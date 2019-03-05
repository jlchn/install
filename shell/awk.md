
It reads from stdin and writes to stdout. It's easy to pipe stuff in and out of it.

Most Awk programs will start with a "{" and end with a "}". Everything in between there gets run once on each line of input.

```
awk '{print $0}'
```
$0 is the entire line, and awk parses the line in to fields for us automatically, using any whitespace (space, tab) as a delimiter, merging consecutive delimiters. Those fields are available to us as the variables $1, $2, $3, etc.

```
echo 'this is a test' | awk '{print $3}'  // prints 'a'
echo 'this is a test' | awk '{print $1,$3}'  // prints 'this a'
echo 'this is a test' | awk '{print $1$3}'  // prints 'thisa'
```
The special variable, NF, contains the number of fields in the current line. 
```
echo 'this is a test' | awk '{print $NF}'  // prints "test"
echo 'this is a test' | awk '{print $1, $(NF-2) }' // prints is
```

Commas between arguments in a print statement put spaces between them, but we can leave out the comma and no spaces are inserted
```
echo 'this is a test' | awk '{print $1,$3}'  // prints 'this a'
echo 'this is a test' | awk '{print $1$3}'  // prints 'thisa'
echo 'this is a test' | awk '{print NR "." $1 "->" $(NF-2)}' // 1.this->is, NR is the current line number

```

how to use them for splitting on a different delimiter

```
echo 'this-is-a test' | awk 'BEGIN{FS="-"}{print $1}'
```

basic if statement

```
echo 'this is a test' | awk '{if($(NF-2) == "is"){print $1}}'
```

variables

```
echo 'this is a line \n this is another line' | awk '{lines+=1}END{print "Total:", lines}' //Total: 2
```
