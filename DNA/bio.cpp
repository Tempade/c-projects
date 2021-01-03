#include <algorithm>
#include <string>
#include <vector>

bool IsValidDNASequence(const std::string& input) {
  // Loops through to check if correct 4 letters are used
  for (auto current : input) {
    bool valid = false;
    if (current == 'A') valid = true;
    if (current == 'T') valid = true;
    if (current == 'C') valid = true;
    if (current == 'G') valid = true;
    if (valid == false) return false;
  }
  return true;
}

void GetReverseComplementSequence(const std::string& input,
                                  std::string* const output) {
  std::string reversed = input;
  std::reverse(reversed.begin(), reversed.end());  // Reverse algorithm
  for (auto current : reversed) {
    if (current == 'A')
      *output += 'T';
    else if (current == 'C')
      *output += 'G';
    else if (current == 'T')
      *output += 'A';
    else if (current == 'G')
      *output += 'C';
    else
      *output += current;
  }
}

std::string GetRNATranscript(const std::string& input) {
  std::string rna_out = "";
  std::string dna_out = "";
  GetReverseComplementSequence(input, &dna_out);
  for (auto current : dna_out) {
    if (current == 'T')
      rna_out += 'U';
    else
      rna_out += current;
  }
  return rna_out;
}

std::vector<std::vector<std::string>> GetReadingFramesAsCodons(
    const std::string& input) {
  std::string original;
  for (auto current : input) {
    if (current == 'T')
      original += 'U';
    else
      original += current;
  }
  std::string originalOne = original;
  originalOne.erase(0, 1);  // offset by 1
  std::string originalTwo = original;
  originalTwo.erase(0, 2);  // offset by 2

  std::string antiParallel = GetRNATranscript(input);
  std::string antiParallelOne = antiParallel;
  antiParallelOne.erase(0, 1);  // offset by 1
  std::string antiParallelTwo = antiParallel;
  antiParallelTwo.erase(0, 2);  // offset by 2

  // Lines 70 - 141 repeat this loop to create vectors
  std::vector<std::string> v_original;
  while (true) {
    if (original.size() >= 3) {
      std::string elements;
      for (int counter(0); counter != 3; counter++) {
        elements += original[counter];
      }
      v_original.push_back(elements);
      original.erase(0, 3);
    } else
      break;
  }
  std::vector<std::string> v_originalOne;
  while (true) {
    if (originalOne.size() >= 3) {
      std::string elements;
      for (int counter(0); counter != 3; counter++) {
        elements += originalOne[counter];
      }
      v_originalOne.push_back(elements);
      originalOne.erase(0, 3);
    } else
      break;
  }
  std::vector<std::string> v_originalTwo;
  while (true) {
    if (originalTwo.size() >= 3) {
      std::string elements;
      for (int counter(0); counter != 3; counter++) {
        elements += originalTwo[counter];
      }
      v_originalTwo.push_back(elements);
      originalTwo.erase(0, 3);
    } else
      break;
  }
  std::vector<std::string> v_antiParallel;
  while (true) {
    if (antiParallel.size() >= 3) {
      std::string elements;
      for (int counter(0); counter != 3; counter++) {
        elements += antiParallel[counter];
      }
      v_antiParallel.push_back(elements);
      antiParallel.erase(0, 3);
    } else
      break;
  }
  std::vector<std::string> v_antiParallelOne;
  while (true) {
    if (antiParallelOne.size() >= 3) {
      std::string elements;
      for (int counter(0); counter != 3; counter++) {
        elements += antiParallelOne[counter];
      }
      v_antiParallelOne.push_back(elements);
      antiParallelOne.erase(0, 3);
    } else
      break;
  }
  std::vector<std::string> v_antiParallelTwo;
  while (true) {
    if (antiParallelTwo.size() >= 3) {
      std::string elements;
      for (int counter(0); counter != 3; counter++) {
        elements += antiParallelTwo[counter];
      }
      v_antiParallelTwo.push_back(elements);
      antiParallelTwo.erase(0, 3);
    } else
      break;
  }

  // Creates the vector of vector of string to return
  std::vector<std::vector<std::string>> output;
  output.push_back(v_antiParallel);
  output.push_back(v_antiParallelOne);
  output.push_back(v_antiParallelTwo);
  output.push_back(v_original);
  output.push_back(v_originalOne);
  output.push_back(v_originalTwo);
  return output;
}

std::string Translate(const std::vector<std::string>& codon_sequence) {
  std::string translation;
  for (auto codon : codon_sequence) {
    if (codon == "GCU") translation += 'A';
    if (codon == "GCC") translation += 'A';
    if (codon == "GCA") translation += 'A';
    if (codon == "GCG") translation += 'A';
    if (codon == "CGU") translation += 'R';
    if (codon == "CGC") translation += 'R';
    if (codon == "CGA") translation += 'R';
    if (codon == "CGG") translation += 'R';
    if (codon == "AGA") translation += 'R';
    if (codon == "AGG") translation += 'R';
    if (codon == "AAU") translation += 'N';
    if (codon == "AAC") translation += 'N';
    if (codon == "GAU") translation += 'D';
    if (codon == "GAC") translation += 'D';
    if (codon == "UGU") translation += 'C';
    if (codon == "UGC") translation += 'C';
    if (codon == "CAA") translation += 'Q';
    if (codon == "CAG") translation += 'Q';
    if (codon == "GAA") translation += 'E';
    if (codon == "GAG") translation += 'E';
    if (codon == "GGU") translation += 'G';
    if (codon == "GGC") translation += 'G';
    if (codon == "GGA") translation += 'G';
    if (codon == "GGG") translation += 'G';
    if (codon == "CAU") translation += 'H';
    if (codon == "CAC") translation += 'H';
    if (codon == "AUU") translation += 'I';
    if (codon == "AUC") translation += 'I';
    if (codon == "AUA") translation += 'I';
    if (codon == "UUA") translation += 'L';
    if (codon == "UUG") translation += 'L';
    if (codon == "CUU") translation += 'L';
    if (codon == "CUC") translation += 'L';
    if (codon == "CUA") translation += 'L';
    if (codon == "CUG") translation += 'L';
    if (codon == "AAA") translation += 'K';
    if (codon == "AAG") translation += 'K';
    if (codon == "AUG") translation += 'M';
    if (codon == "UUU") translation += 'F';
    if (codon == "UUC") translation += 'F';
    if (codon == "CCU") translation += 'P';
    if (codon == "CCC") translation += 'P';
    if (codon == "CCA") translation += 'P';
    if (codon == "CCG") translation += 'P';
    if (codon == "UCU") translation += 'S';
    if (codon == "UCC") translation += 'S';
    if (codon == "UCA") translation += 'S';
    if (codon == "UCG") translation += 'S';
    if (codon == "AGU") translation += 'S';
    if (codon == "AGC") translation += 'S';
    if (codon == "ACU") translation += 'T';
    if (codon == "ACC") translation += 'T';
    if (codon == "ACA") translation += 'T';
    if (codon == "ACG") translation += 'T';
    if (codon == "UGG") translation += 'W';
    if (codon == "UAU") translation += 'Y';
    if (codon == "UAC") translation += 'Y';
    if (codon == "GUU") translation += 'V';
    if (codon == "GUC") translation += 'V';
    if (codon == "GUA") translation += 'V';
    if (codon == "GUG") translation += 'V';
    if (codon == "UAG") translation += '*';
    if (codon == "UGA") translation += '*';
    if (codon == "UAA") translation += '*';
  }
  return translation;
}

std::string GetLongestOpenReadingFrame(const std::string& DNA_sequence) {
  std::vector<std::vector<std::string>> readingFrames =
      GetReadingFramesAsCodons(DNA_sequence);
  std::string lorf = "";  // Longest open reading frame
  for (auto frame : readingFrames) {
    std::string current = Translate(frame);
    std::string temp;  // reading frame to compare with longest
    bool active = false;
    for (auto letter : current) {
      if (letter == 'M') active = true;
      if (active == true) temp += letter;
      if (letter == '*') {
        active = false;
        if (temp.size() > lorf.size()) lorf = temp;
        temp = "";  // clears the temporary reading frame
      }
    }
  }
  return lorf;
}