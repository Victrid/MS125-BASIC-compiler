# BASIC RISC-V Compiler

This is the BASIC RISC-V compiler homework of MS125: Principle and Practice of Computer Algorithms.

This compiler realizes a simplest BASIC to hex-formatted RISC-V machine code, which can be executed with [this RISC-V simulator](https://github.com/Victrid/RISC-V-simulator/tree/compiler-variation). The compiler uses a stack model, only uses a few registers to do all actions.

## Build and Run

To build binary executables, please run `make` in the root directory. This will generate following files, and a RISC-V simulator core `riscv-core` from [simulator](https://github.com/Victrid/RISC-V-simulator/tree/compiler-variation) submodule.

**Note**: You need to initiate submodules. Cf. [Git book: submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules) for cloning with submodules. 

**Note**: The submodule cloning part could consume a lot of time due to GitHub’s accessibility in your location.

|     Name     | Purpose                                             |
| :----------: | --------------------------------------------------- |
|   `lexer`    | Convert BASIC code into processable marks.          |
|  `orderer`   | Adjust expression calculation order.                |
|  `cfgizer`   | Regularize variable symbols and jumping.            |
| `translator` | Generate into a human-readable RISC-V assembly.     |
| `asmpreproc` | Calculate jump distances and replace pseudo labels. |
|     `as`     | Assemble into RISC-V machine code for `riscv-core`. |

All executables can receive up to 2 arguments. Take `as` for an example:

|          command           |   input    |    output    |
| :------------------------: | :--------: | :----------: |
|           `./as`           |  `stdin`   |   `stdout`   |
|      `./as some.asm`       | `some.asm` |   `stdout`   |
| `./as some.asm some.riscv` | `some.asm` | `some.riscv` |

You can use a pipe (`|`) to generate the `.riscv` machine code like this way:

`./lexer path/to/your/basic/code | ./orderer | ./cfgizer | ./translator | ./asmpreproc | ./as > some.riscv`

## Tests

Test cases are located in [testfiles/testcases](testfiles/testcases). 

Run automatic tests with: `make case_test`. 

Cf. [testscript readme](testscript/README.md) for details.

**Note**: Due to the stack model, test `control_1` could take up to 10 minutes to execute. 