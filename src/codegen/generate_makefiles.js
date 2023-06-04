var C_COMPILER = "i686-linux-gnu-gcc";
var C_COMPARGS = "-ffreestanding -O2 -Wall -Wextra -no-pie";

var ASSEMBMER  = "i686-linux-gnu-as";
var ASSMARGS   = ""

var ENABLE_DEBUG = false;

var fs = require("fs");
var cp = require("child_process");

var getDirectories = (source = "") => {
    return fs.readdirSync(source, { withFileTypes: true }).filter(dirent => dirent.isDirectory()).map(dirent => dirent.name)
}

var folders = getDirectories(".");
var actualCodeFolders = [];

var crtbegin = cp.execSync(`${C_COMPILER} ${C_COMPARGS} -print-file-name=crtbegin.o`);
var crtend = cp.execSync(`${C_COMPILER} ${C_COMPARGS} -print-file-name=crtend.o`);

if (ENABLE_DEBUG) {
    if (ASSMARGS != "") ASSMARGS += " -g";
    else ASSMARGS = "-g";

    C_COMPARGS += " -g";
}

var env_codetree = {
    CODEDIRS: [],
    FILES: [],
    CC: C_COMPILER,
    CARGS: C_COMPARGS  
};
var file_start = "";
var file_end = "";

folders.forEach((folder) => {
    var isBranch = true;
    var files = [];
    var file_start1 = "";
    var file_end1 = "";
    fs.readdirSync(folder).forEach(file => {
        if (!isBranch) return;

        if (file.endsWith(".js") || file.endsWith(".h") || fs.lstatSync(`${folder}/${file}`).isDirectory() )  {
            isBranch == false;
        } else {
            var name = file.split(".")[0];

            if (!file.endsWith(".cfg") && file != "Makefile") { 
                if (file.endsWith("crti.asm")) {
                    file_start1 = `../build/${folder}/${name}.o`; 
                } else if (file.endsWith("crtn.asm")) {
                    file_end1 = `../build/${folder}/${name}.o`;
                }

                files.push(file);
            }
        }
    });

    if(isBranch && files.length != 0) {
        actualCodeFolders.push({
            "folder": folder,
            "files": files
        })
        if (file_start1 != "") file_start = file_start1;
        if (file_end1 != "") file_end = file_end1;
    }
});

actualCodeFolders.forEach((branch) => {
    var makefile = `CPARAMS=${C_COMPARGS}
.RECIPEPREFIX = >

all:
> @mkdir ../../build -p
> @mkdir ../../build/${branch.folder} -p
`;

    branch.files.forEach((file) => {
        makefile += `
> @echo Compiling ${branch.folder}/${file} ...
        `;

        var name = file.split(".")[0];

        if (file.endsWith(".c")) {
            makefile += `
> @${C_COMPILER} -c ${file} $(CPARAMS) -o ../../build/${branch.folder}/${name}.o 
            `;
        }
        if (file.endsWith(".asm")) {
            makefile += `
> @${ASSEMBMER} ${file} ${ASSMARGS} -o ../../build/${branch.folder}/${name}.o 
            `;
        }

        env_codetree.FILES.push(`../build/${branch.folder}/${name}.o`);
    })

    makefile += `
> @echo ${branch.folder} branch done.
    `

    env_codetree.CODEDIRS.push(branch.folder);

    fs.writeFileSync(`${branch.folder}/Makefile`, makefile);
});

var env_codetree_string = "CODEDIRS=";

env_codetree.CODEDIRS.forEach((codedir) => {
    env_codetree_string += `${codedir} `;
});

var crtbeginstr = crtbegin.toString("utf8");
var crtendstr = crtend.toString("utf8");

crtbeginstr = crtbeginstr.trim();
crtendstr = crtendstr.trim();

env_codetree_string += `\nFILES=`;

if (file_start != "") env_codetree_string += `${file_start} `

env_codetree_string += `${crtbeginstr} `;

env_codetree.FILES.forEach((file) => {
    if(file == file_start || file == file_end) return;
    env_codetree_string += `${file} `;
});

env_codetree_string += `${crtendstr} ${file_end}
CC=${env_codetree.CC}
CARGS=${env_codetree.CARGS}
`;

fs.writeFileSync("codetree", env_codetree_string);