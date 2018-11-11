1. ENUM is usually used for self-reference.
2. You should use enum types any time you need to represent a fixed set of constants. 

### Basic usage

```java
public enum Day {
    MONDAY,TUESDAY,WEDNESDAY,THURSDAY,FRIDAY,SATURDAY,SUNDAY
}
```

#### 1.print enum 

```java
    System.out.println(Day.MONDAY);//MONDAY
    System.out.println(Day.TUESDAY);//TUESDAY
    System.out.println(Day.WEDNESDAY);//WEDNESDAY
    System.out.println(Day.TUESDAY);//TUESDAY
    System.out.println(Day.FRIDAY);//FRIDAY
    System.out.println(Day.SATURDAY);//SATURDAY
    System.out.println(Day.SUNDAY);//SUNDAY
```

#### 2.loop enum

```java
    for (Day day : Day.values()){
        System.out.println(day);
    }
```

#### 3.compare enum

```java
    Day day = Day.FRIDAY;
    System.out.println(day==Day.FRIDAY);
```

#### 4.switch enum

```java
        Day day = Day.FRIDAY;
        switch (day){
            case MONDAY:
                System.out.println(0);
                break;
            case TUESDAY:
                System.out.println(1);
                break;
            case WEDNESDAY:
                System.out.println(2);
                break;
            case THURSDAY:
                System.out.println(3);
                break;
            case FRIDAY:
                System.out.println(4);
                break;
            case SATURDAY:
                System.out.println(5);
                break;
            case SUNDAY:
                System.out.println(6);
                break;
        }
```

#### 5.get enum by string
```java
        Day day = Day.valueOf("FRIDAY");
        System.out.println(day);//FRIDAY
        day = Day.valueOf("WRONG");
        System.out.println(day);//Exception in thread "main" java.lang.IllegalArgumentException: No enum constant com.company.Day.WRONG

```