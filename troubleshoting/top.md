### display all processes
```shell 
top
```

- display processes with order
    - order by CPU
        - this is default behavior
        - press `P`
    - order by Memory
        - press `M`
    - order by process id
        - press `N`
    - order by the running time
        - press `T`
    - show in reverse order
        - press `R`
- highlight the sorted column
    - press `xb`
- display full path command
    - press `c`
- display in parent-child hierachy
    - press `V`
- display all CPU core data
    - press `1`
- display with filters
    - display processes of some user
        - press `u` 
        - enter the user name, empty indicates all
    - limit numbers of output
        - press `n`
        - enter a number, 0 indicates all
    - show/toggle idle/sleeping processes
        - press `i`
    - filter by custom criterias
        - press `o`
        - add filter expresssion
            - COMMAND=java
            - %CPU>0.2
            - %MEM>10.2
- hide or show columns
    - press `f`
    - press `up/down` to navigate among items
    - press `d` to toggle show or hide
    - press `q` to quit and back to the process list
    