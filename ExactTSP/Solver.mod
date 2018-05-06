/*********************************************
 * OPL 12.7.1.0 Model
 * Author: Anna Bonaldo
 * Creation Date: 06/mag/2018 at 15:48:34
 *********************************************/
// problem size 
int n =...;
int gridLine =...; 
range holesN = 1..n; 
string filename ="model.txt"; 

// random = 0 GRID
// random = 1 RAND 
// random = 2 SEMIGRID
int random = 1; 

int seedY = 100;
int seedX = 100;  
int base = 2; 
int cloudSize = 100; 
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
//setof(move) moves = {<i, j> |i, j in holesN}; 
float c[moves];

// edges costs 
position  holePositions[holesN];  // holes coordinates
// preprocessing 
// random location

// decision variables 
dvar boolean y[moves]; // arches in path
dvar int+ x[moves];

execute {
	
	function getTimeOfMomement(position1, position2){
		return 	Opl.sqrt(
		Opl.pow(position1.x-position2.x, 2)+ 
		Opl.pow(position1.y-position2.y, 2)); 		
	}
	
	
    var num = n;
   
       if(random == 1)
    {
        
   // 	var ofile = new IloOplOutputFile(n+"RAND"+cloudSize+filename); 		
		for (var i in holesN)
		{
			holePositions[i].x= Opl.rand(cloudSize); 
			holePositions[i].y= Opl.rand(cloudSize); 	
		//	ofile.writeln(holePositions[i].x, " ", holePositions[i].y); 
		}
	//	ofile.close();
	}	
	
	if(random == 0) 
	{
		var ofile = new IloOplOutputFile(num+"GRID"+filename); 		
		var offset = 0.0; 
		
		for (var i=0; i<n; i++)
		{		
			var m = (i % gridLine); 	
			if(m == 0)	
				offset = offset+base; 
			
			holePositions[i+1].x= m; 
			holePositions[i+1].y= offset; 
			ofile.writeln(holePositions[i+1].x, " ", holePositions[i+1].y); 
		}
		ofile.close(); 
		
	}	
	
	 if(random == 2) 
	 {	
	 	var ofile = new IloOplOutputFile(num+"SEMIGRID"+filename); 	
		var offset = 0.0; 
		for (var i=0; i<n; i++)
		{		
			var m = (i % gridLine); 	
			if(m == 0)	
				offset = offset+base; 
			holePositions[i+1].x= m +Opl.rand(seedX)*0.01;  
			holePositions[i+1].y= offset+ Opl.rand(seedY)*0.01; 
			ofile.writeln(holePositions[i+1].x, " ", holePositions[i+1].y); 
		}		
		ofile.close(); 
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

	 // 1 //
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
	
	
	var result = "sample.csv";
	var mode = "GRID";
		if(random == 1) mode ="RAND";
		if(random == 2) mode ="SEMIGRID";
	var ofile = new IloOplOutputFile("costs"); 
	
//for(var sample =0; sample < 10; sample++){
//	ofile.writeln("SAMPLE; ", sample, ";");

	for (var size = 5; size <= 200; size+=5) {
		//var size = 100; 
		var MyCplex = new IloCplex(); 
		var opl = new IloOplModel(mod, MyCplex); 
		dat.n = size; 	
		dat.gridLine = Opl.sqrt(size); 
		opl.addDataSource(dat); 
		// generate every time dat has been changed
		opl.generate(); // model generation with new data
			
		// solving + check it has been solved
		if(MyCplex.solve()) {		
		     writeln(" --Solution: " +MyCplex.getBestObjValue()+" Problem size:  "+size+ " in time = "+ MyCplex.getCplexTime());	
//			 ofile.writeln("Solution;", MyCplex.getBestObjValue(), 
//			";Problem size; ", size,
//			 ";Time; ", MyCplex.getCplexTime());  	
			ofile.writeln(opl.printSolution())
					 }
		opl.end(); 
		MyCplex.end(); 

//	}	
  }	
	//ofile.close(); 
	writeln("End execution");			
}


 