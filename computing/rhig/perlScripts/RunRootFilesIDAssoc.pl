#!/bin/perl
system "root4star -q macros/JetYields/RootFileNPartNSIDAssoc.C'(1.0)'";
system "mv Pics/YieldFits/*.png Pics/YieldFits/10/.";
system "root4star -q macros/JetYields/RootFileNPartNSIDAssoc.C'(1.5)'";
system "mv Pics/YieldFits/*.png Pics/YieldFits/15/.";
system "root4star -q macros/JetYields/RootFileNPartNSIDAssoc.C'(2.0)'";
system "mv Pics/YieldFits/*.png Pics/YieldFits/20/.";
system "root4star -q macros/JetYields/RootFileNPartNSIDAssoc.C'(3.0)'";
system "mv Pics/YieldFits/*.png Pics/YieldFits/30/.";

