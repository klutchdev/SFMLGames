#!/opt/homebrew/bin/zsh                                                                               #
# =================================================================================================== #
#   AUTOMATIC CPP SFML COMPILATION TOOL                                                               #
#       ©2022 Kyle "Klutch" Leary                                                                     #
# =================================================================================================== #
# Generates and runs a compiler script dynamically from the cpp project                               #
# files, times the operation, then saves it in a markdown file code block                             #
# =================================================================================================== #
BEGIN=$SECONDS        # Start run timer                                                               #
DIRECTORY="${0%/*}"   # Current directory                                                             #
MD="compileScript.md" # File to save data                                                             #
# =================================================================================================== #
FILES=()                                                                                # Filenames   #
LIB=("-lsfml-graphics" "-lsfml-window" "-lsfml-system" "-lsfml-audio" "-lsfml-network") # SFML libs   #
# =================================================================================================== #
for cppfile in "${DIRECTORY}"/*.cpp; do # Get current directory *.cpp filenames                       #
  FILES+=($cppfile)                     # Push cpp filename to FILES array                            #
done                                    # All current directory *.cpp files added                     #
# =================================================================================================== #
g++ -g ${FILES[@]} -o prog ${LIB[@]} # Run newly generated script                                     #
TT=$((SECONDS - BEGIN))              # Stop timer, calculate duration                                 #
# =================================================================================================== #
echo "### Compile\n" >$MD                             # Write file                                    #
echo "\`g++ -g ${FILES[@]} -o prog ${LIB[@]}\`" >>$MD # Add code block                                #
echo "#### Files compiled: ${#FILES}" >>$MD           # Files counter                                 #
echo "#### Duration: ${TT}s" >>$MD                    # Compile time                                  #
echo "Files compiled: ${#FILES}"                      # Files counter                                 #
echo "Duration: ${TT}s"                               # Compile time                                  #
exit 0                                                # Terminate                                     #
# =================================================================================================== #
