var C_COMPILER = "i686-linux-gnu-gcc";
var ASSEMBMER  = "i686-linux-gnu-as";

var fs = require("fs");

var getDirectories = (source = "") => {
    return fs.readdirSync(source, { withFileTypes: true }).filter(dirent => dirent.isDirectory()).map(dirent => dirent.name)
}

var folders = getDirectories(".");
var actualCodeFolders = [];

var env_codetree = {
    CODEDIRS: [],
    FILES: []
};

folders.forEach((folder) => {
    var isBranch = true;
    var files = [];
    fs.readdirSync(folder).forEach(file => {
        if (!isBranch) return;

        if (file.endsWith(".js") || file.endsWith(".h"))  {
            isBranch == false;
        } else {
            if (!file.endsWith(".cfg") && file != "Makefile") files.push(file);
        }
    });

    if(isBranch && files.length != 0) {
        actualCodeFolders.push({
            "folder": folder,
            "files": files
        })
    }
});

actualCodeFolders.forEach((branch) => {
    var makefile = `CPARAMS=-ffreestanding -O2 -Wall -Wextra
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
> @${ASSEMBMER} ${file} -o ../../build/${branch.folder}/${name}.o 
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

env_codetree_string += "\nFILES=";

env_codetree.FILES.forEach((file) => {
    env_codetree_string += `${file} `;
});

fs.writeFileSync("codetree", env_codetree_string);