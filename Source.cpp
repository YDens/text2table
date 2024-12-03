#include <iostream> 

#include <fstream> 

 

 

 

int main(int argc, char* argv[]) { 

 

 if (argc != 3) { 

  std::cout << "Use: \n" 

   << "text2table source destination \n"; 

  return 1; 

 } 

 

 std::ifstream inFile(argv[1]); 

 if (!inFile) { 

  std::cerr << "Can not open file '" << argv[1] << "'\n"; 

  return 2; 

 } 

 

 //1.        

 int lenwords[200] = { 0 }; 

 int wordlen = 0; 

 int wordnum = 0; 

 int ch; 

 while (EOF != (ch = inFile.get())) { 

  if (' ' == ch || '\t' == ch) { //   

   if (wordlen != 0) { 

    if (lenwords[wordnum] < wordlen) { 

     lenwords[wordnum] = wordlen; 

    } 

    wordlen = 0; 

    ++wordnum; 

   } 

  } 

  else if (ch == '\n') { //     

   if (lenwords[wordnum] < wordlen) { 

    lenwords[wordnum] = wordlen; 

   } 

   wordlen = 0; 

   wordnum = 0; 

  } 

  else { 

   ++wordlen; 

  } 

 } 

 if (wordlen != 0) { 

  if (lenwords[wordnum] < wordlen) { 

   lenwords[wordnum] = wordlen; 

  } 

 } 

 

 //2.         ,          

 

 inFile.clear(); //   (   ) 

 inFile.seekg(0);//seekg -  0-  

 

 std::ofstream outFile(argv[2]); 

 if (!outFile.is_open()) { 

  std::cout << "Can not write to file '" << argv[2] << "\n"; 

  inFile.close(); 

  return 3; 

 } 

 

 wordlen = 0; 

 wordnum = 0; 

 int charcounter = 0; 

 while (EOF != (ch = inFile.get())) { 

  if (' ' == ch || '\t' == ch) {  

   if (wordlen != 0) { 

    ++wordnum; 

    wordlen = 0; 

 

   } 

  } 

  else if (ch == '\n') {  

   outFile.put('\n'); 

   wordlen = 0; 

   wordnum = 0; 

   charcounter = 0; 

  } 

  else { 

   if (wordlen == 0 && wordnum > 0) {  

    while (charcounter <= lenwords[wordnum - 1]) { 

     outFile.put(' '); 

     ++charcounter; 

    } 

    charcounter = 0; 

   } 

   outFile.put(ch); 

   ++wordlen; 

   ++charcounter; 

  } 

 } 

 

 inFile.close(); 

 outFile.close(); 

 return 0; 

}

