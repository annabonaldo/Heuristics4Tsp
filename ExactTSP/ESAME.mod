/*********************************************
 * OPL 12.7.1.0 Model
 * Author: Anna Bonaldo
 * Creation Date: 06/feb/2018 at 13:41:21
 *********************************************/
// problem size 
int n =...;
int iter =...;
int seed =...;
int gridLineSize= ...; 
range cities = 1..n; 
string filename ="model.txt"; 
string dataMode = ...; 
int sample[1..4] = [10, 50, 100, 200]; 
int seedarray[0..9] = [111, 5, 2500, 184, 21, 47, 66, 71, 32, 84]; 

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
			
		if(dataMode == "RAND") // random 
		{
			var ofile = new IloOplOutputFile(n+"RANDsample"+iter+filename); 				
			Opl.srand(seed); 
			for (var i in cities)
			{		
				holePositions[i].x= Opl.rand(n); // cloud of the same size of problem
				holePositions[i].y= Opl.rand(n); // cloud of the same size of problem
				ofile.writeln(holePositions[i].x, " ", holePositions[i].y); 
			}
			ofile.close();
		}	
		else 
		if(dataMode == "CONSTGRID")// grid constant
		{
			var ofile = new IloOplOutputFile(n+"CONSTGRIDsample"+iter+filename); 				
			var offset = 0.0; 
			for (var i in cities)
			{
			  	var m = (i % gridLineSize); 		
		 		if(m == 0)	{offset = offset+1.0; }	
				holePositions[i].x= m; 
				holePositions[i].y= offset; 
				ofile.writeln(holePositions[i].x, " ", holePositions[i].y); 
			}	
		}	
		else if(dataMode == "SEMIGRID")// grid constant
		{
			var ofile = new IloOplOutputFile(n+"SEMIGRIDsample"+iter+filename); 				
			var offset = 0.0; 
			for (var i in cities)
			{
			  	var m = (i % gridLineSize); 		
		 		if(m == 0)	{offset = offset+1.0; }	
				holePositions[i].x= m + Opl.rand(sqrt(n));  
				holePositions[i].y= offset+ Opl.rand(sqrt(n)); 
				ofile.writeln(holePositions[i].x, " ", holePositions[i].y); 
			}	
		}	
		else 
		if(dataMode == "CONSTRAND50")// grid constant
		{
			var ofile = new IloOplOutputFile(n+"CONSTRAND50sample"+iter+filename); 				
			Opl.srand(seed); 
			for (var i in cities)
			{		
				holePositions[i].x= Opl.rand(50); // cloud of size 50
				holePositions[i].y= Opl.rand(50); // cloud of size 50
				ofile.writeln(holePositions[i].x, " ", holePositions[i].y); 
			}
		}	
		else 
		if(dataMode == "CONSTRAND5000")// grid constant
		{
			var ofile = new IloOplOutputFile(n+"CONSTRAND5000sample"+iter+filename); 				
			Opl.srand(seed); 
			for (var i in cities)
			{		
				holePositions[i].x= Opl.rand(5000); // cloud of size 5000
				holePositions[i].y= Opl.rand(5000); // cloud of size 5000
				ofile.writeln(holePositions[i].x, " ", holePositions[i].y); 
			}
		}	
		
		
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
	var  mode = "CONSTRAND50";  	
	var file =  mode+"exactStats.txt";
	var ofile = new IloOplOutputFile(file); 
  
   for (var actualMode = 0; actualMode<2; actualMode++)
   if(actualMode == 0)
   mode = "CONSTRAND50"; 
   if (actualMode == 1)
   mode = "CONSTRAND5000"; 
     for (var s = 1; s<5; s++) // sizes  
    {      
        writeln("Iteration sample ", i);          
		var MyCplex = new IloCplex(); 
		var opl = new IloOplModel(mod, MyCplex); 

		var size = thisOplModel.sample[s]; 
		dat.n = thisOplModel.sample[s]; 
		dat.iter =i ; 
		dat.gridLineSize = Opl.sqrt(size); 
		dat.dataMode = mode; 
		dat.seed = thisOplModel.seedarray[i]
		opl.addDataSource(dat); 
		// generate every time dat has been changed
		opl.generate(); // model generation with new data
		
		if(dat.n <101) {	
		if(MyCplex.solve()) {		
		     writeln("Mode "+ mode+ ": Solved problem -- size:  " +size+ " in time = "+ MyCplex.getCplexTime()+ 
		     		" Solution value: "+ MyCplex.getObjValue()); 
		     		
			 ofile.writeln("Solution;", MyCplex.getObjValue(),
			";Problem size; ", size, 
			 ";Time; ", MyCplex.getCplexTime(),
			 "; Sample iter; ",i,";"+
			 " EXACT; "+ "dataset; "+mode+";"); 			 		 		 		
	    } }	    

		opl.end(); 
		MyCplex.end(); 
				   	    		  	
  } 	
//  ofile.close(); 
  
  mode = "SEMIGRID"; 
    for (var s = 1; s<5; s++) // sizes 
    {
   for (var i = 0; i< 10; i++) //samples
   {     
        writeln("Iteration sample ", i);        
		var MyCplex = new IloCplex(); 
		var opl = new IloOplModel(mod, MyCplex); 

		var size = thisOplModel.sample[s]; 
		dat.n = thisOplModel.sample[s]; 
		dat.iter =i ; 
		dat.gridLineSize = Opl.sqrt(size); 
		dat.dataMode = mode; 
		dat.seed = thisOplModel.seedarray[i]
		opl.addDataSource(dat); 
		// generate every time dat has been changed
		opl.generate(); // model generation with new data
			
		if(dat.n <101) {	
		if(MyCplex.solve()) {		
		     writeln(("Mode "+ mode+":Solved problem -- size:  " +size+ " in time = "+ MyCplex.getCplexTime()+ 
		     		" Solution value: "+ MyCplex.getObjValue())+ " seed :"+dat.seed); 
		     		
			
			 ofile.writeln("Solution;", MyCplex.getObjValue(),
			 ";Problem size; ",  size,
			 ";Time; ", MyCplex.getCplexTime(),
			 "; Sample iter; ",i,";"+
			 " EXACT; "+ "dataset; "+mode+"; seed; ",dat.seed,";");  				 		
	    } }	    

		opl.end(); 
		MyCplex.end(); 
				   	    		
	}  // end 10 samples iteration    
	
  } // end sizes iteration 
  	
  ofile.close();   
  writeln("End execution");		
}
