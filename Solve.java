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
int n;
long m;
float f;
char c;
boolean b;

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
     ArrayList<Integer> al = new ArrayList<Integer>();
     al.forEach((n)->{ System.out.println(n);});
     Collections.sort(al, (o1, o2) -> (o1 > o2) ? -1 : (o1 < o2) ? 1 : 0);
}

// End
}