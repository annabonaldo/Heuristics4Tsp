/*********************************************
 * OPL 12.7.1.0 Model
 * Author: Anna Bonaldo
 * Creation Date: 06/mag/2018 at 15:48:34
 *********************************************/
// problem size 
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
tuple position{
 	float x; 
	float y; 
}

position  holePositions[cities];  // holes coordinates

// decision variables 
dvar boolean x[edges]; // arches in path
dvar float+  u[2..n];

execute {
function getTimeOfMomement(city1, city2){
		return 	Opl.sqrt(
		Opl.pow(city1.x-city2.x, 2)+ 
		Opl.pow(city1.y-city2.y, 2)); 		
	}

	var ofile = new IloOplOutputFile(num+"SEMIGRID"+filename); 	
	  /*  var offset = 0.0;	 
		for (var i in cities)
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
		ofile.close(); */
		var ofile = new IloOplOutputFile(n+"RAND"+filename); 		
		for (var i in holesN)
		{
			holePositions[i].x= Opl.rand(100); 
			holePositions[i].y= Opl.rand(100); 	
			if(generateModelToFile>0)ofile.writeln(holePositions[i].x, " ", holePositions[i].y); 
		}
		ofile.close();
		
	for (var e in moves)
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
