var table = [
    [0, false], [1, false], [2, false],
    [3, false], [4, false], [5, false],
    [6, false], [7, false], [8, true],
    [9, false], [10, true], [11, true],
    [12, true], [13, true], [14, true],
    [15, false], [16, false], [17, true],
    [18, false], [19, false], [20, false],
    [21, false], [22, false], [23, false],
    [24, false], [25, false], [26, false],
    [27, false], [28, false], [29, false],
    [30, true], [31, false]
]

var list_global = "";
var list_assembly = "";
var list_full = "";

var pattern_isr_noerr = (int = 0) => {
    var res = `isr_stub_${int}:
    pushad
    cld
    push ${int}
    call __idt_interrupt_handler
    popad
    iret

`;
    return res;
}

var pattern_isr_err = (int = 0) => {
    var res = `isr_stub_${int}:
    pushad
    cld
    push ${int}
    call __idt_exception_handler
    popad
    iret

`;
    return res;
}

list_global = ".section .text\n"

table.forEach((obj) => {
    list_assembly += (obj[1]) ? pattern_isr_err(obj[0]) : pattern_isr_noerr(obj[0]);
    list_global += `.global isr_stub_${obj[0]}\n.type isr_stub_${obj[0]}, @function\n`;
});

list_global += "\n.intel_syntax noprefix\n";

list_full = `${list_global}\n${list_assembly}`;

console.log(list_full);

console.log("\n-------------\nC function declarations:\n");

table.forEach((obj) => {
    // list_assembly += (obj[1]) ? pattern_isr_err(obj[0]) : pattern_isr_noerr(obj[0]);
    // list_global += `.global isr_stub_${obj[0]}\n.type isr_stub_${obj[0]}, @function\n`;
    console.log(`extern void isr_stub_${obj[0]}();`);
});

console.log("\n-------------\nArray:\n");

table.forEach((obj) => {
    // list_assembly += (obj[1]) ? pattern_isr_err(obj[0]) : pattern_isr_noerr(obj[0]);
    // list_global += `.global isr_stub_${obj[0]}\n.type isr_stub_${obj[0]}, @function\n`;
    console.log(`__idt_stub_table[${obj[0]}] = isr_stub_${obj[0]};`);
});
