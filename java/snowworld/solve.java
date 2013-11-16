import java.util.*;


class Edge
{
    int to;
    int from;
    double snow;    
    public Edge(int to, int from, double snow){
        this.to = to;
        this.from = from;
        this.snow = snow;
    }    
    public int getTo() {
        return to;
    }
    public int getFrom() {
        return from;
    }
    public double getSnow() {
        return snow;
    }
}


class solve
{
    static ArrayList<Edge> getEdgeList(int e, Scanner reader){
        //Scanner reader = new Scanner(System.in);    
        ArrayList<Edge> edges = new ArrayList<Edge>();
        for(int i = 0; i < e; i++){
            edges.add(new Edge(reader.nextInt(), reader.nextInt(), 
                        reader.nextDouble()));  
        }
        return edges;
        
    }
    static int[][] adjacencyMatrix(int n, ArrayList<Edge> edges){
        int adjMat[][] = new int[n][n];
        for(int i = 0; i < edges.size(); i++){
            adjMat[edges.get(i).getTo()][edges.get(i).getFrom()] = 1;
            adjMat[edges.get(i).getFrom()][edges.get(i).getTo()] = 1;
        }
        return adjMat;
    }  
    static void solve(){
        /*Unimplemented */
        return;
    }
    
    
    public static void main (String[] args)
    {
        Scanner reader = new Scanner(System.in);
        int n;
        int e;
        double alpha;
        n = reader.nextInt();
        e = reader.nextInt();
        alpha = reader.nextDouble();
        
        ArrayList<Edge> edges = getEdgeList(e, reader);
        int[][] adjMat = adjacencyMatrix(n, edges);        
        
        solve();

        return;
    }
    
    
    
}
