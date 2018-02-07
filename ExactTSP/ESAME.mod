/*********************************************
 * OPL 12.7.1.0 Model
 * Author: Anna Bonaldo
 * Creation Date: 06/feb/2018 at 13:41:21
 *********************************************/
// problem size 
int n =...;
int gridLine =...; 
range holesN = 1..n; 
string filename ="model.txt"; 
int random = 1; 
int generateModelToFile = 0; 
int seedY = 5;
int seedX = 5; 
int base = 10; 
// generate random data

tuple position{
 	float x; 
	float y; 
}

tuple move {
	int i; 
	int j;
}

setof(move) moves = {<i, j> |i, j in holesN: i!=j}; 
float c[moves];

// edges costs 
position  holePositions[holesN];  // holes coordinates
// preprocessing 
// random location

// decision variables 
dvar boolean y[moves]; // arches in path
dvar int+ x[moves];

execute {
	function getTimeOfMomement(city1, city2){
		return 	Opl.sqrt(
		Opl.pow(city1.x-city2.x, 2)+ 
		Opl.pow(city1.y-city2.y, 2)); 		
	}
	
    var num = n;
   if(generateModelToFile>0){
       if(random == 1)
    {
		var ofile = new IloOplOutputFile(n+"RAND"+filename); 		
		for (var i in holesN)
		{
			holePositions[i].x= Opl.rand(100); 
			holePositions[i].y= Opl.rand(100); 	
			if(generateModelToFile>0)ofile.writeln(holePositions[i].x, " ", holePositions[i].y); 
		}
		ofile.close();
	}	
	
	if(random == 0) 
	{
		var ofile = new IloOplOutputFile(num+"GRID"+filename); 		
		var offset = 0.0; 
		for (var i in holesN)
		{
		  var m = (i % gridLine); 		
		  if(m == 0)	
		{	
			offset = offset+1.0; 
		}	
			holePositions[i].x= m; 
			holePositions[i].y= offset; 
			ofile.writeln(holePositions[i].x, " ", holePositions[i].y); 
		}
		ofile.close(); 
		
	}	
	
	 if(random == 2) 
	 {	
	 	var ofile = new IloOplOutputFile(num+"SEMIGRID"+filename); 	
		var offset = 0.0; 
		for (var i in holesN)
		{
		  var m = (i % gridLine); 		
		  if(m == 0)	
			{	
				offset = offset+base; 
			}	
			holePositions[i].x= m +seedX; 
			holePositions[i].y= offset+ +Opl.rand(seedX); 
			ofile.writeln(holePositions[i].x, " ", holePositions[i].y); 
		}		
		ofile.close(); 
	 }	
} 
else
{
       if(random == 1)
    {			
		for (var i in holesN)
		{
			holePositions[i].x= Opl.rand(100); 
			holePositions[i].y= Opl.rand(100); 				
		}
	}	
	
	 if(random == 0) 
	 {	
		var offset = 0.0; 
		for (var i in holesN)
		{
		  var m = (i % gridLine); 		
		  if(m == 0)	
			{	
			offset = offset+1.0; 
			}	
			holePositions[i].x= m; 
			holePositions[i].y= offset; 
		}		
	 }	
	 
	 if(random == 2) 
	 {	
		var offset = 0.0; 
		for (var i in holesN)
		{
		  var m = (i % gridLine); 		
		  if(m == 0)	
			{	
				offset = offset+base; 
			}	
			holePositions[i].x= m +seedX; 
			holePositions[i].y= offset+ +Opl.rand(seedX); 
		}		
	 }	

	}	
	
	for (var e in moves)
	{	
		c[e] = getTimeOfMomement(holePositions[e.i], holePositions[e.j]); 
	}
}

dexpr float TotalDrillTime  = sum (m in moves) c[m]*y[m]; 
minimize TotalDrillTime; 


subject to 
{
  	  flow_one: 
  	   sum(j in holesN: (j!=1))  x[<1,j>] == 1; 
  	   
    // 2 //
    forall(k in holesN)
      sum(i in holesN: i!=k)  x[<i,k>] -sum(j in holesN: k!=k)  x[<k,j>] == 1; 
    
	// 3 // incoming edge num eq to one 
  	forall (j in holesN )
  	  flow_in: 
  	  sum(i in holesN: i!=j) y[<i,j>] == 1; 
  	
  	// 4 // outcoming edge num eq to one 
  	forall (i in holesN)
  	  flow_out: 
  	   sum(j in holesN: i!=j) y[<i,j>] == 1; 
  	
     // 5 //
     forall(i in holesN){
       forall(j in holesN: i!=j){
              
       x[<i, j>] <= n * y[<i,j>] ;
    }} 
} 


main {
	var mod = thisOplModel.modelDefinition; 
	var dat = thisOplModel.dataElements; 
	var random = 1;
	
	
	var result = "result.csv";
	var mode = "RAND";
		if(random ==1 ) mode ="GRID";
		if(random == 2) mode ="SEMIGRID";
	var ofile = new IloOplOutputFile(mode+result); 
	
for(var sample =0; sample < 10; sample++){
	ofile.writeln("SAMPLE ", sample);

	for (var size = 5; size <= 200; size+=5) {
		var MyCplex = new IloCplex(); 
		var opl = new IloOplModel(mod, MyCplex); 
		dat.n = size; 	
		dat.gridLine = Opl.sqrt(size); 
		opl.addDataSource(dat); 
		// generate every time dat has been changed
		opl.generate(); // model generation with new data
			
		// solving + check it has been solved
		if(MyCplex.solve()) {		
		     writeln("Solved problem with size:  "+size+ " in time = "+ (float)MyCplex.getCplexTime());	
			 ofile.writeln("Solution;", MyCplex.getObjValue(), 
			";Problem size; ", size,
			 ";Time; ", MyCplex.getCplexTime());  	
			 }
		opl.end(); 
		MyCplex.end(); 
	}	
	
}	
	ofile.close(); 
	writeln("End execution");			
}


 