#!/bin/perl
#void MakeEtaProjection(bool CuCu,float assocLow, float assocHigh,float trigLow,float trigHigh,int cb1,int cb2)

#CuCu
@assocLow = (1.0,1.5,2.0);
@trigLow = (3.0,4.0);
for($i=0;$i<3;$i++){
	for($j=0;$j<2;$j++){
		system "root4star -b -q macros/QM08/MakeEtaProjection.C\'(true,$assocLow[$i],6,$trigLow[$j],6,1,1)\'\n";
		system "root4star -b -q macros/QM08/MakeEtaProjection.C\'(true,$assocLow[$i],6,$trigLow[$j],6,1,3)\'\n";
		system "root4star -b -q macros/QM08/MakeEtaProjection.C\'(true,$assocLow[$i],6,$trigLow[$j],6,1,6)\'\n";
		system "root4star -b -q macros/QM08/MakeEtaProjection.C\'(true,$assocLow[$i],6,$trigLow[$j],6,3,6)\'\n";

                system "root4star -b -q macros/QM08/MakeEtaProjection.C\'(false,$assocLow[$i],6,$trigLow[$j],6,1,2)\'\n";
                system "root4star -b -q macros/QM08/MakeEtaProjection.C\'(false,$assocLow[$i],6,$trigLow[$j],6,1,5)\'\n";
                system "root4star -b -q macros/QM08/MakeEtaProjection.C\'(false,$assocLow[$i],6,$trigLow[$j],6,1,5)\'\n";
                system "root4star -b -q macros/QM08/MakeEtaProjection.C\'(false,$assocLow[$i],6,$trigLow[$j],6,1,9)\'\n";
                system "root4star -b -q macros/QM08/MakeEtaProjection.C\'(false,$assocLow[$i],6,$trigLow[$j],6,5,9)\'\n";
	}
}




