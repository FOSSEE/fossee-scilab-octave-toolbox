

//cd /home/rupak/scilab-toolbox/scilab_octave/

//if (~isfile("build.sce")) then
//    cd ../../
//end
//pwd

try exec unloader.sce
end

exec cleaner.sce
clear

try ulink
end

//help_from_sci("macros","help/en_US")
exec builder.sce
exec loader.sce

//octave_fun()
