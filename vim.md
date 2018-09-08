### mode

normal mode : `ESC`

insert mode : `i`

visual block (select column): `CTRL + v`

visual character(select range of text) : `v`

visual line (select entire line): `V`



---

### selection 

visual block (select column): `CTRL + v`

visual character(select range of text) : `v`

visual line (select entire line): `V`

select current word : `viw`



---

### save and change file

save to disk : :`w`

save as : `saveas <path/to/file>`

open file : `:e <path/to/file>`

change file : `:bn` or `:bp` 



---

### redo and undo

redo : `CTRL + r`

undo : `u`



---

### copy and paste

copy current line : `y`

paste after : `p`

paste before : `P`



---

### delete

in normal mode 

delete current char under the cursor : `x`

delete current word : `diw`

delete and copy current line : `dd`



---

### insert 

in normal mode 

insert after the cusor : `a`

insert new line before current line: `O`

insert new line after current line : `o`

replace from current cursor to the end of the word : `cw`

insert # to the start of multiple lines : `CTRL v ,j , I #, ESC `

insert # to the end of multiple lines : `CTRL v ,j , A #, ESC `



---

### basic cursor move

#### move among lines

go to first line : `G`

go to last line : `gg`

go to nth line :`nG`

#### move among a word

go to the start of the word : `w`

go to the end of the word : `e`

#### move in a line 

go to the start of the line : `0`

go to the end of the line : `$`

go to next occurence of letter `a`  on the line : `fa` . backward : `F`

go to the postion that just before char `a` on the line : `ta` . backward : `T`


### Search/Replace

```
/pattern - search for pattern
?pattern - search backward for pattern
n - repeat search in same direction
N - repeat search in opposite direction
:%s/old/new/g - replace all old with new throughout file
:%s/old/new/gc - replace all old with new throughout file with confirmations
```

### Working with multiple files

```
:e filename - Edit a file in a new buffer
:bnext (or :bn) - go to next buffer
:bprev (of :bp) - go to previous buffer
:bd - delete a buffer (close a file)
:sp filename - Open a file in a new buffer and split window
ctrl+ws - Split windows
ctrl+ww - switch between windows
ctrl+wq - Quit a window
ctrl+wv - Split windows vertically
```