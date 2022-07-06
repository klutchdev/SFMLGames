#!/opt/homebrew/bin/zsh                                                            #
# =================================================================================#
#   AUTOMATIC CPP SFML COMPILATION TOOL                                            #
#       ©2022 Kyle "Klutch" Leary                                                  #
# ================================================================================ #
# Generates and runs a compiler script dynamically from the cpp project            #
# files, times the operation, then saves it in a markdown file code block          #
# ================================================================================ #
CC=g++                                                # CPP Compiler               #
CPP=-std=c++11                                        # CPP Version                #
ARGS=("-g")                                           # Enable debugging           #
DIRECTORY="${0%/*}"                                   # Current directory          #
OUT="-o prog"                                         # Output build file          #
FILES=()                                              # Filenames array            #
LIBS=()                                               # Linked libs                #
SFML=("graphics" "window" "system" "audio" "network") # SFML libs                  #
MD="compileScript.md"                                 # File to save data          #
BEGIN=$SECONDS                                        # Start run timer            #
# ================================================================================ #
for lib in ${SFML}; do  # Get SFML libs without the prefix                         #
  LIBS+=("-lsfml-$lib") # Push '-lsfml-lib' array                                  #
done                    # All linked SFML libraries added                          #
# ================================================================================ #
for cppfile in ${DIRECTORY}/*.cpp; do # Get current directory *.cpp filenames      #
  FILES+=("$cppfile")                 # Push cpp filename to FILES array           #
done                                  # All current directory *.cpp files added    #
# ================================================================================ #
$CC $CPP ${ARGS[@]} ${FILES[@]} $OUT ${LIBS[@]} # Run newly generated script       #
TT=$((SECONDS - BEGIN))                         # Stop timer, calculate duration   #
# ================================================================================ #
echo "### Compile\n" >$MD                                        # Write file      #
echo "\`$CC $CPP ${ARGS[@]} ${FILES[@]} $OUT ${LIBS[@]}\`" >>$MD # Add code block  #
echo "#### Files compiled: ${#FILES}" >>$MD                      # Files counter   #
echo "#### Duration: ${TT}s" >>$MD                               # Compile time    #
echo "Files compiled: ${#FILES}"                                 # Files counter   #
echo "Duration: ${TT}s"                                          # Compile time    #
exit 0                                                           # Terminate       #
# ================================================================================ #
