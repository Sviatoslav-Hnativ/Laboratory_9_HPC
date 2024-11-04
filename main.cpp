#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

void printArray(const std::vector<int>& arr) {
    
    for (int num : arr) {
    
        std::cout << num << " ";
    
    }
    std::cout << std::endl;
}

void bubbleSort(std::vector<int>& arr) {
   
    int n = arr.size();
    std::cout << "Sequential Bubble Sort process:" << std::endl;
    
    for (int i = 0; i < n - 1; ++i) {
    
        for (int j = 0; j < n - i - 1; ++j) {
     
            if (arr[j] > arr[j + 1]) {
               
                std::cout << "Swapping " << arr[j] << " and " << arr[j + 1] << ": \n";
                std::swap(arr[j], arr[j + 1]);
                
                std::cout <<"Array element swap:\t";
                printArray(arr); 
            }
        }

        if (i < n - 2) {
            
            std::cout << "End of iteration " << i + 1 << ": ";
            printArray(arr);
        }
    }
}

void parallelBubbleSort(std::vector<int>& arr) {
    
    int n = arr.size();
    bool swapped;

    std::cout << "Parallel Bubble Sort process:" << std::endl;
   
    for (int i = 0; i < n - 1; ++i) {
        
        swapped = false;

        #pragma omp parallel for
        
        for (int j = 0; j < n - i - 1; ++j) {
            
            if (arr[j] > arr[j + 1]) {
               
                #pragma omp critical 
               
                {
                    std::cout << "Swapping elements at indices " << j << " and " << j + 1
                              << " (values " << arr[j] << " and " << arr[j + 1] << ")" << std::endl;
                }
             
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        std::cout << "Array after iteration " << i + 1 << ": ";
        printArray(arr);

        if (!swapped) break;  
    }
}

void oddEvenSort(std::vector<int>& arr) {
   
    int n = arr.size();
    int phase, i, temp;
   
    std::cout << "Odd-Even Transposition Sort process:" << std::endl;
   
    for (phase = 0; phase < n; phase++) {
   
        if (phase % 2 == 0) {
   
            std::cout << "Even phase: \n";
   
            for (i = 1; i < n; i += 2) {
   
                if (arr[i - 1] > arr[i]) {
   
                    std::cout << "Swapping " << arr[i - 1] << " and " << arr[i] << " at indices " << i - 1 << " and " << i << "\n";
                    
                    temp = arr[i - 1];
                    arr[i - 1] = arr[i];
                    arr[i] = temp;
                }
            }
        } else {
            
            std::cout << "Odd phase: \n";
            
            for (i = 1; i < n - 1; i += 2) {
            
                if (arr[i] > arr[i + 1]) {
            
                    std::cout << "Swapping " << arr[i] << " and " << arr[i + 1] << " at indices "<< i << " and " << i + 1 << "\n";
                    
                    temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                }
            }
        }
        
        std::cout << "Result phase sorting: ";
        printArray(arr);
    }
}

int main() {
    
    std::vector<int> arr = {5, 3, 8, 4, 2, 10, 2,2323, 32, 3 };
    std::vector<int> arrCopy;
     
    std::cout << "Unsorted array: ";
    printArray(arr); 
    
    std::cout << "---------------------------------------------------------------------------"<<std::endl;
    
    arrCopy = arr; 

    
    auto start = std::chrono::high_resolution_clock::now();
    
    bubbleSort(arrCopy);
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;  

    std::cout << "Bubble Sort sorted array: ";
    
    printArray(arrCopy);
    
    std::cout << "Bubble Sort execution time: " << duration.count() << " seconds\n\n"; 

    std::cout << "---------------------------------------------------------------------------"<<std::endl;
    
    arrCopy = arr;
    start = std::chrono::high_resolution_clock::now();
    
    parallelBubbleSort(arrCopy);
    
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    std::cout << "Parallel Bubble Sort sorted array: ";
    
    printArray(arrCopy);
    
    std::cout << "Parallel Bubble Sort execution time: " << duration.count() << " seconds\n\n";

    std::cout << "---------------------------------------------------------------------------"<<std::endl;
   
    arrCopy = arr;
    start = std::chrono::high_resolution_clock::now();
    
    oddEvenSort(arrCopy);
    
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    std::cout << "Odd-even transposition sorted array: ";
    
    printArray(arrCopy);
    
    std::cout << "Execution time: " << duration.count() << " seconds\n";
    
    return 0;
}
