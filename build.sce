try exec unloader.sce
end

exec cleaner.sce
clear

try ulink
end

help_from_sci("macros","help/en_US")
exec builder.sce
exec loader.sce
