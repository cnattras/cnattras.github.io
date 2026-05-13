#!/bin/perl



#Cut set 1
system "root4star -b -q macros/Omega/MakeOmegaPlot.C'\(\"rootFiles/correlations/correlations-2-0-omegaCuts1.root\",\"rootFiles/correlations/correlations-1-0-omegaCuts1.root\",\"Cut1MB\"\)'\n";
system "root4star -b -q macros/Omega/MakeOmegaPlot.C'\(\"rootFiles/correlations/correlations-HTMBMB-combined-2-0-omegaCuts1.root\",\"rootFiles/correlations/correlations-HTMBMB-combined-1-0-omegaCuts1.root\",\"Cut1MBHT\"\)'\n";

#Cut set 2
system "root4star -b -q macros/Omega/MakeOmegaPlot.C'\(\"rootFiles/correlations/correlations-2-0-omegaCuts2.root\",\"rootFiles/correlations/correlations-1-0-omegaCuts1.root\",\"Cut2MB\"\)'\n";
system "root4star -b -q macros/Omega/MakeOmegaPlot.C'\(\"rootFiles/correlations/correlations-HTMBMB-combined-2-0-omegaCuts2.root\",\"rootFiles/correlations/correlations-HTMBMB-combined-1-0-omegaCuts1.root\",\"Cut2MBHT\"\)'\n";

#Cut set 3
system "root4star -b -q macros/Omega/MakeOmegaPlot.C'\(\"rootFiles/correlations/correlations-2-0-omegaCuts3.root\",\"rootFiles/correlations/correlations-1-0-omegaCuts1.root\",\"Cut3MB\"\)'\n";
system "root4star -b -q macros/Omega/MakeOmegaPlot.C'\(\"rootFiles/correlations/correlations-HTMBMB-combined-2-0-omegaCuts3.root\",\"rootFiles/correlations/correlations-HTMBMB-combined-1-0-omegaCuts1.root\",\"Cut3MBHT\"\)'\n";
