# generates the folders for each day and each challange
for i in {1..25}
do
    echo "Creating folder for day ${i}..."
    mkdir ./day_${i}
    mkdir ./day_${i}/challange_1
    mkdir ./day_${i}/challange_2
done
exit 0