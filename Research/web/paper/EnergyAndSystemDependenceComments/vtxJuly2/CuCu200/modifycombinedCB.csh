#!/bin/tcsh
sed -i 's/comparisonManyStandardCB0to60/comparisonManyStandardCB0to10/' combinedCB1.C

sed -i 's/CentBin1/CentBin2/g' combinedCB2.C
sed -i 's/CB1/CB2/g' combinedCB2.C
sed -i 's/cb1/cb2/g' combinedCB2.C
sed -i 's/comparisonManyStandardCB0to60/comparisonManyStandardCB10to20/' combinedCB2.C

sed -i 's/CentBin1/CentBin3/g' combinedCB3.C
sed -i 's/CB1/CB3/g' combinedCB3.C
sed -i 's/cb1/cb3/g' combinedCB3.C
sed -i 's/comparisonManyStandardCB0to60/comparisonManyStandardCB20to30/' combinedCB3.C

sed -i 's/CentBin1/CentBin4/g' combinedCB4.C
sed -i 's/CB1/CB4/g' combinedCB4.C
sed -i 's/cb1/cb4/g' combinedCB4.C
sed -i 's/comparisonManyStandardCB0to60/comparisonManyStandardCB30to40/' combinedCB4.C

sed -i 's/CentBin1/CentBin5/g' combinedCB5.C
sed -i 's/CB1/CB5/g' combinedCB5.C
sed -i 's/cb1/cb5/g' combinedCB5.C
sed -i 's/comparisonManyStandardCB0to60/comparisonManyStandardCB40to50/' combinedCB5.C

sed -i 's/CentBin1/CentBin6/g' combinedCB6.C
sed -i 's/CB1/CB6/g' combinedCB6.C
sed -i 's/cb1/cb6/g' combinedCB6.C
sed -i 's/comparisonManyStandardCB0to60/comparisonManyStandardCB50to60/' combinedCB6.C