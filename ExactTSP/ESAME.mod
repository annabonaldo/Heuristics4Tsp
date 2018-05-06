/*********************************************
 * OPL 12.7.1.0 Model
 * Author: Anna Bonaldo
 * Creation Date: 06/feb/2018 at 13:41:21
 *********************************************/
// problem size 
int n = 12;
range cities = 1..n; 
float A[cities][cities] = [
[ 0.0,	 5.5,	 4.3,	 6.5,	12.0,	15.3,	17.5,	11.5,	10.8,	18.0,	19.0,	18.0],
[ 5.5,	 0.0,	 2.3,	 5.0,	10.8,	13.4,	15.0,	 6.5,	 5.5,	12.8,	17.5,	13.0],
[ 4.3,	 2.3,	 0.0,	 3.2,	 9.8,	12.0,	14.0,	 7.3,	 7.0,	13.5,	14.7,	15.0],
[ 6.5,	 5.0,	 3.2,	 0.0,	 6.0,	 9.0,	11.2,	 7.0,	 8.3,	13.0,	14.5,	16.8],
[12.0,	10.8,	 9.8,	 6.0,	 0.0,	 3.2,	 5.8,	 9.5,	12.0,	13.0,	15.0,	20.3],
[15.3,	13.4,	12.0,	 9.0,	 3.2,	 0.0,	 2.7,	10.7,	13.7,	12.6,	15.0,	21.3],
[17.5,	15.0,	14.0,	11.2,	 5.8,	 2.7,	 0.0,	11.2,	14.5,	11.6,	14.0,	21.3],
[11.5,	 6.5,	 7.3,	 7.0,	 9.5,	10.7,	11.2,	 0.0,	 3.3,	 6.5,	 7.5,	11.0],
[10.8,	 5.5,	 7.0,	 8.3,	12.0,	13.7,	14.5,	 3.3,	 0.0,	 8.0,	 8.5,	 8.5],
[18.0,	12.8,	13.5,	13.0,	13.0,	12.6,	11.6,	 6.5,	 8.0,	 0.0,	 2.3,	11.0],
[19.0,	17.5,	14.7,	14.5,	15.0,	15.0,	14.0,	 7.5,	 8.5,	 2.3,	 0.0,	 9.3],
[18.0,	13.0,	15.0,	16.8,	20.3,	21.3,	21.3,	11.0,	 8.5,	11.0,	 9.3,	 0.0]

];

tuple edge {
	int i; 
	int j;
}

setof(edge) edges = {<i, j> |i, j in cities: i!=j }; 

float c[edges];



// decision variables 
dvar boolean x[edges]; // arches in path
dvar float+  u[2..n];

execute {
	
	for (var e in edges)
	{	
		c[e] = A[e.i][e.j]; 
	}
}

dexpr float TotalDistance  = sum (e in edges) c[e]*x[e]; 
minimize TotalDistance; 
subject to 
{

	forall(j in cities)
	  flow_in: 
	  sum(i in cities: i!=j) x[<i,j>] == 1;
	  
	forall(i in cities)
	  flow_out: 
	  sum(j in cities: j!=i) x[<i,j>] == 1;
	 
	 forall(i in cities: i >1, j in cities: j>1 && j!=i)
	   u[i]-u[j]+(n-1)*x[<i,j>] <= n-2; 
	  
} 


main {
	var mod = thisOplModel.modelDefinition; 

		var size = 12; 
		var MyCplex = new IloCplex(); 
		var opl = new IloOplModel(mod, MyCplex); 
	
		//opl.addDataSource(dat); 
		// generate every time dat has been changed
		opl.generate(); // model generation with new data
			
		// solving + check it has been solved
		if(MyCplex.solve()) {		
		     writeln(" --Solution: " +MyCplex.getBestObjValue()+" Problem size:  "+size+ " in time = "+ MyCplex.getCplexTime());	
//			 ofile.writeln("Solution;", MyCplex.getBestObjValue(), 
//			";Problem size; ", size,
//			 ";Time; ", MyCplex.getCplexTime());  	
			//ofile.writeln(opl.printSolution())
					 }
					 writeln(opl.printSolution()); 
		opl.end(); 
		MyCplex.end(); 


	//ofile.close(); 
	writeln("End execution");			
}


 