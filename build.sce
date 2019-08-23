

cd /home/rupak/scilab-toolbox/scilab_octave/

if (~isfile("build.sce")) then
    cd ../../
end
pwd

try exec unloader.sce
end

exec cleaner.sce
clear
ulink


exec builder.sce
exec loader.sce

//octave_fun()
