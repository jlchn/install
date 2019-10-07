### Dependency
To use Gson, add following to pom.xml  
``` xml
<dependency>
    	<groupId>com.google.code.gson</groupId>
    	<artifactId>gson</artifactId>
    	<version>2.6.2</version>
</dependency>
```

### Convert java object to json string
```java
User user = new User();
String userInString = new Gson().toJson(user);
```

### Convert json string to java object
```java
User user = new Gson().from(userInString,User.class);
```
### Convert json array to java List
```java
String jsonInstring = "[{\"tenant\":\"Google\"}, {\"tenant\":\"Facebook\"}]";
List<Customer> list = gson.fromJson(jsonInString, new TypeToken<List<Customer>>(){}.getType());
list.forEach(x -> System.out.println(x));
```
### Convert json to java Map
```java
String jsonInstring = "{\"tenant\":\"Google\", \"landscape\":"develop"}";
Map<String, Object> map = gson.fromJson(jsonInString, new TypeToken<Map<String, Object>>(){}.getType());
map.forEach((x,y)-> System.out.println( x + "-" + y));
```


