/*********************************************
 * OPL 12.7.1.0 Model
 * Author: Anna Bonaldo
 * Creation Date: 06/feb/2018 at 13:41:21
 *********************************************/
// problem size 
int n =...;
int iter =...;
range cities = 1..n; 
string filename ="model.txt"; 
int sample[1..5] = [10, 50, 100, 200]; 

tuple position{
 	float x; 
	float y; 
}

position  holePositions[cities];  // holes coordinates

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
	function getTimeOfMomement(city1, city2){
		return 	Opl.sqrt(
		Opl.pow(city1.x-city2.x, 2)+ 
		Opl.pow(city1.y-city2.y, 2)); 		
	}

		var ofile = new IloOplOutputFile(n+"RANDsample"+iter+filename); 		
		for (var i in cities)
		{
			holePositions[i].x= Opl.rand(n); // cloud of the same size of problem
			holePositions[i].y= Opl.rand(n); // cloud of the same size of problem
			ofile.writeln(holePositions[i].x, " ", holePositions[i].y); 
		}
		ofile.close();
		
	for (var e in edges)
	{	
		c[e] = getTimeOfMomement(holePositions[e.i], holePositions[e.j]); 
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
	var dat = thisOplModel.dataElements; 	
	var file = "RANDexactStats.csv";
	var ofile = new IloOplOutputFile(file); 
     for (var i = 0; i< 10; i++)
     {
     writeln("Iteration sample ", i);      
     
     for (var s = 1; s<6; s++)
     {
		var MyCplex = new IloCplex(); 
		var opl = new IloOplModel(mod, MyCplex); 
	
		var size = thisOplModel.sample[s]; 
		dat.n = thisOplModel.sample[s]; 
		dat.iter =i ; 
		
		opl.addDataSource(dat); 
		// generate every time dat has been changed
		opl.generate(); // model generation with new data
			
		// solving + check it has been solve,
		if(MyCplex.solve()) 
		{		
		     writeln("Solved problem with size:  " +size+ " in time = "+ MyCplex.getCplexTime()+ " Solution value: "+ MyCplex.getObjValue()); 
			 ofile.writeln("Solution;", MyCplex.getObjValue(),";Problem size; ", size, ";Time; ", MyCplex.getCplexTime(),"; Sample iter; ",i,";");  	
	    }
		opl.end(); 
		MyCplex.end(); 
		ofile.close(); 
		   	    		
		}   
	}	    
 writeln("End execution");		
}
/*********************************************
 * OPL 12.7.1.0 Model
 * Author: Anna Bonaldo
 * Creation Date: 23/mag/2018 at 18:01:43
 *********************************************/
