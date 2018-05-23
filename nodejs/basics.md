### event
```javascript
var events = require('events');
var emitter = new  events.EventEmitter() ;
emitter.on ('event1',function(msg){
    console.log(msg);
});

emitter.on ('event2',function(obj){
    console.log(obj);
});
//-------------------
emitter.emit('event1','message');
var obj = { id : '1' , name : 'name'} ;
emitter.emit('event2',obj);
```
### event to avoid callback hell 

```javascript
var fs = require( 'fs' );
var fileName = 'use_event_to_avoid_callback_hell.js';
var EventEmitter = require( 'events' ).EventEmitter;
var util = require( 'util' );

var fileReader = function() {
    var _self = this;
    EventEmitter.call( _self );
    _self.on( 'stats', function() {
        fs.stat( fileName, function( err, stats ) {
            if ( !err && stats.isFile() ) {
                _self.emit( 'read' );
            }
        } );

    } );

    _self.on( 'read', function() {
        fs.readFile( fileName, 'utf-8', function( err, data ) {
            if ( !err && data ) {
                console.log( data );
            };
        } );
    } );

    _self.read = function() {
        fs.exists( fileName, function( exists ) {
            if ( exists ) {
                _self.emit( 'stats' );
            }
        } );
    }


}
util.inherits( fileReader, EventEmitter );

var reader = new fileReader();
reader.read();

```
 
### require and modules 
_require is used to import a module into your program_   

#### core modules 
core modules are modules compiled into node binary , they are given the highest precedence by require(),which means that in the event of a module-naming conflict , the core module is loaded . for example , a call to __fs__ will always load the core __fs__ module .  

#### file modules 
file modules are non-core modules . 

#### module search orders 
if a module path does not correspond to a core module , an absolute path or a relative path , then node begin to search node_modules folders .  
>1.core module  
>2.file module  
>3.node_modules folders in the calling script`s parent directory,if not found , level up the directory tree and find again , util the module is found or the root of the directory structure is reached .   
>4.if require() does not find an exact match , it attempts to add _.js_,_.json_,_.node_ file extensions . and then find again .

#### locate a module path
```javascript
require.resolve('fs');//fs
```

### the module object

Node provide an object __module__ in every file to represent the current module.  
__module__ has a property __exports__ , which is an empty object by default .the value of __exports__ is returned by __require__ method .  

##### module.exports as a function
```javascript
// foo.js
module.exports = function(){
    console.log('in the foo.js');
}

// bar.js
var foo = require('./foo.js');// the module.exports of foo.js is a function 
foo();
```

##### module.exports as an object 
```javascript
// foo.js
module.exports.foo = function(){
    console.log('in the foo.js');
}

// bar.js
var foo = require('./foo.js');// the module.exports of foo.js is an object 
foo.foo();
```

### console.log()

```javascript
//source code of log
Console.prototype.log = function(){
    this._stdout.write(util.format.apply(this,arguements)+'\n');
};

//format output

var util = require('util');
var format = util.format("%s , %d , %j " ,name , age , json);
console.log(format);

//other print functions
util.log('this is a test');//29 Aug 18:04:19 - this is a test
```
