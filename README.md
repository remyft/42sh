# 42sh
_A fully functional shell from scratch in C_

## Build & Run

```bash
git clone https://github.com/remyft/42sh.git
cd 42sh && make
```
Now you can run your shell, or test it with unit test.
**Launch:**
```bash
./42sh
```
**Unit testing :**
```bash
./42sh unittest/unittest_all
```

## Project's details

*Mandatory part:*
- Full edition of commands line
- Redirection and aggregation operators `>` `>>` `<` `<<` `>&` `<&`
- Pipe `|`
- Separators `;`
- Logical operators `&&` `||`
- Built-ins `cd` `echo` `exit` `type`
- Monitoring of intern shell variables such as:
  - Intern variable creation and exportation
  - built-in `set`
  - Local variable `HOME=/tmp cd`
- Exit code access `${?}`
- Job control monitoring:
  - built-ins `jobs` `fg` `bg`
  - Operator and separator `&`
  - Monitoring of all signals
- Each built-ins must be written as posix-standart
- All of the terminal and command line handling using the termcaps library

*Modulart part:*
- Inhibitors `" (double quote)`, `' (simple quote)` and `\`
- Pattern matching (globing): `*`, `?`, `[]`, `!` and the characters intervals with `\` (back-slash)
- Tilde expansion and additional parameter formats:
  - `~`
  - `$(paramater:-word}`
  - `$(paramater:=word}`
  - `$(paramater:?word}`
  - `$(paramater:+word}`
  - `$(#paramater}`
  - `$(paramater%}`
  - `$(paramater%%}`
  - `$(paramater#}`
  - `$(parameter##}
- Control subsitution `$()`
- Contextual dynamic completion
- Alias management `alias`, `unalias`
- built-ins `test` with options: `texttt-b, -c, -d, -e, -f, -g, -L -p, -r, -S, -s, -u, -w, -x, -z, =, !=, -eq, -ne, -ge, -                                    lt, -le, !.` 

*Bonus:*
- Autocompletion for everything (like zsh)
- Compliant to POSIX Standart
- Auto search of folders files ( like zsh )
- Built-ins with lots of options
- Globing with completion ( like zsh )
- Unitest comparison with Bash
- non interactive mode `42sh <file>`

## Author

* [Rémy Fontaine](https://github.com/remyft)
* [Gilles Bourgeois](https://github.com/gbourgeo)
* [Tsitsi Sadaghashvili](https://github.com/tsitsi314)
* [Dorian Baffier](https://github.com/dbaffier)
