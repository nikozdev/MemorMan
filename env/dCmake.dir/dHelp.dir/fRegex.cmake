cmake_minimum_required(VERSION 3.3...3.8)
include_guard(GLOBAL)
# actions
function(fRegexIgnoreRBracket vRegex)
    string(REPLACE "(" "\\(" ${vRegex} ${${vRegex}})
    string(REPLACE ")" "\\)" ${vRegex} ${${vRegex}})
    set(${vRegex} ${${vRegex}} PARENT_SCOPE)
endfunction(fRegexIgnoreRBracket)
function(fRegexIgnoreSBracket vRegex)
    string(REPLACE "[" "\\[" ${vRegex} ${${vRegex}})
    string(REPLACE "]" "\\]" ${vRegex} ${${vRegex}})
    set(${vRegex} ${${vRegex}} PARENT_SCOPE)
endfunction(fRegexIgnoreSBracket)
function(fRegexIgnoreCBracket vRegex)
    string(REPLACE "{" "\\{" ${vRegex} ${${vRegex}})
    string(REPLACE "}" "\\}" ${vRegex} ${${vRegex}})
    set(${vRegex} ${${vRegex}} PARENT_SCOPE)
endfunction(fRegexIgnoreCBracket)
function(fRegexIgnoreABracket vRegex)
    fRegexIgnoreRBracket(${vRegex} ${${vRegex}})
    fRegexIgnoreSBracket(${vRegex} ${${vRegex}})
    fRegexIgnoreCBracket(${vRegex} ${${vRegex}})
    set(${vRegex} ${${vRegex}} PARENT_SCOPE)
endfunction(fRegexIgnoreABracket)
