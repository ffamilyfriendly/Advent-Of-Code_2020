#how the generated cpp files should look
gen_cpp="
int main(int argc,  char** argv) {
    
}"

# generates the folders for each day and each challange
for i in {1..25}
do
    echo "Creating folder for day ${i}..."
    mkdir ./day_${i}
    mkdir ./day_${i}/challange_1
    mkdir ./day_${i}/challange_2
    echo "${gen_cpp}" > ./day_${i}/challange_1/main.cpp
    echo "${gen_cpp}" > ./day_${i}/challange_2/main.cpp
    echo -e "all:\n\t\tg++ ./challange_1/main.cpp -o ./challange_1.exe && g++ ./challange_2/main.cpp -o ./challange_2.exe" > ./day_${i}/makefile
done
exit 0