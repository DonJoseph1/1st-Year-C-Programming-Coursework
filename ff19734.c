/*Don Issac Joseph*/

#include <stdio.h>
#include <math.h>


//Function to find the sum of the elements of an array
double sumArray(double arr[],double n){

double sum = 0;
int ii;

/*A loop to add the elements of an array*/
for(ii=0;ii<=n;ii++){

    sum += arr[ii];
}
return(sum);/*Return sum*/

}

//Main program
int main() {

FILE *iText, *oText;

// Variable declaration
char letterU, letterX;
double u0,U,delx,dx,dt,u0Sum,uSum,uMean,T,doubleN;
int jj,ii,intN,iter;


//Open file
iText = fopen ("input.txt","r");


//Continue if file opens correctly
if (iText != NULL){


//Read to the end of the file
    while(feof(iText) == 0)  {

        //Read file in//
        fscanf(iText,"%c %lf \n %c %lf", &letterU,&U,&letterX,&delx);

        // Ensure correct reading of input values from file
        if (letterU == 'U'){
                u0 = U;
}
            else if (letterX == 'X'){
                    dx = delx;
}
}

//Close file
fclose(iText);
}

    //Print "-1" to the answer file if the input file doesn't open properly
    else {
        oText = fopen("answer.txt","w");
        fprintf(oText,"-1");
}

//Calculate the number of nodes
doubleN = 1+(1/dx);
intN = doubleN; /*Convert the double form of N into integer form*/

//Determine the time increment after each iteration
dt = 0.5*pow(dx,2);

//Declare arrays
double oldT[intN-1]; /*Array to store temperatures from previous iteration*/
double newT[intN-1]; /*Array to store new updated temperatures*/


//Set the initial temperature conditions (at t=0) to start and end nodes
oldT[0] = 0;
oldT[intN-1] = 0;


//Open loop to set initial conditions to the remaining (middle) nodes
for (ii =1; ii<=intN-2;ii++){

        oldT[ii] = u0;
}

//Calculate the initial average temperature of the bar
u0Sum = sumArray(oldT,(intN-1));
uMean = (u0Sum/intN);


//Loop to find the temperatures of the nodes at each time level
iter = 0; /*Set the iteration counter to zero*/

while (uMean>=0.1){

    iter++;/*Count the number of iterations carried out*/
    uSum = 0;

    //Set initial conditions to second temperature array
    newT[0] = 0;
    newT[intN-1] = 0;

    //Update temperature from second node to middle node
    for (jj=1; jj<=((intN+1)/2);jj++){

        //Use the formula to find the new temperature
        newT[jj] = oldT[jj] + 0.5*(oldT[jj+1]-2*oldT[jj]+oldT[jj-1]);
}

    //Update temperature from second to last node to middle node
    for (jj=(intN-2);jj>=((intN+1)/2);jj--){

        //Use the formula to find the new temperature
        newT[jj] = oldT[jj] + 0.5*(oldT[jj+1]-2*oldT[jj]+oldT[jj-1]);
}

    //Call the sum function to find sum of the temperatures along the bar
    uSum = sumArray(newT,(intN-1));

    //Find the average temperature of the bar
    uMean = uSum/intN;

    //Store the updated temperatures into the oldT array
    for(jj=0;jj<=intN-1;jj++){

        oldT[jj] = newT[jj];

}
}

//Initialise a value of T to later check if a suitable value of T has been calculated
T = -2;

//Calculate time taken for the average temperature to reduce to 0.1 units
T = dt*iter;

//Open answer file
oText = fopen("answer.txt","w");

//Check if no errors in answer or input dx value
if (dx > 0 || T > 0) {

    fprintf(oText,"%lf",T);
}

    //Print "-1" to answer file if there's an error
    else {

        fprintf(oText,"-1");
}

return (0);
}

