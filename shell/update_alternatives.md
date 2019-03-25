### update-alternatives

it is used to set or allow users to choose the default programs they want to use.

For example, if the text editors `vim` and `nano` are both installed on the system, the alternatives system will set the name /usr/bin/editor  to  refer  to
`/usr/bin/nano` by default. The users can override this and cause it to refer to `/usr/bin/vim.tiny` instead.


```
sudo  update-alternatives --config editor
[sudo] password for XXXXXX: 
There are 5 choices for the alternative editor (providing /usr/bin/editor).

  Selection    Path                Priority   Status
------------------------------------------------------------
* 0            /bin/nano            40        auto mode
  1            /bin/ed             -100       manual mode
  2            /bin/nano            40        manual mode
  3            /usr/bin/code        0         manual mode
  4            /usr/bin/vim.basic   30        manual mode
  5            /usr/bin/vim.tiny    15        manual mode

Press <enter> to keep the current choice[*], or type selection number: 5

```

### /var/log/alternatives.log

logs to record the results of `update-alternatives`.

```
update-alternatives 2019-03-25 19:08:40: link group editor updated to point to /usr/bin/vim.tiny
```
