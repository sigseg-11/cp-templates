// https://codeforces.com/contest/1348/submission/119576836
import java.util.*;
import java.io.*;
import java.time.*;
import java.text.*;
import java.math.*;
class Solve{

// Start
public record Point(int x, int y){}
String s;
static int n = 5;
long m;
float f;
char c;
boolean b;
// Byte, Short, Integer, Long, Float, and Double wrapper classes are all subclasses of the Number class.
// The wrapper classes BigDecimal and BigInteger are not one of the primitive wrapper classes but are immutable.
static Integer nc = 55;


BitSet bs = new BitSet();
ArrayList<Integer> al = new ArrayList<Integer>();
Set<String> st = new TreeSet<>();
HashSet<ArrayList> hs = new HashSet<>();
TreeMap<Integer, String> tm = new TreeMap<Integer, String>();
HashMap<String, Integer> hm = new HashMap<>();
PriorityQueue<Integer> pq = new PriorityQueue<Integer>();
// Pair <String, Integer> pp = new Pair <String, Integer> ();
// Triplet<Integer, String, String> tp = new Triplet<Integer, String, String>();

static void dbg(Object... o){System.err.println(Arrays.deepToString(o));}

public static void main(String args[]){  
     Scanner sc = new Scanner(System.in); 
     String name = sc.nextLine();
     System.out.println("Hello " + name);  
     long N = sc.nextLong(); 

     for(long i = 0, j = N; j > -1 && i <= N; --j,++i){
        System.out.print(i+" "+j);
     }
     System.out.print('\n');

     ArrayList<Integer> al = new ArrayList<Integer>();
     // vector<int>* v = new vector<int>(), *b = new vector<int>();
     // Collections takes class

     System.out.println(nc);
     System.out.println(n);
     al.forEach((n)->{ System.out.println(n);});
     Collections.sort(al, (o1, o2) -> (o1 > o2) ? -1 : (o1 < o2) ? 1 : 0);
}

// End
}

// Static variables are used for defining constants because their values can be retrieved by invoking the class without creating an instance of it. Static variables can be initialized outside the member function or class definition.
// A static method in Java is a method that is part of a class rather than an instance of that class. Every instance of a class has access to the method. Static methods have access to class variables (static variables) without using the class's object (instance). Only static data may be accessed by a static method.