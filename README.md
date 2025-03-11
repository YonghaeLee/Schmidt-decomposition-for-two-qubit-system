# Formulas for Mutually Orthogonal Quantum States in Two-Qubit Systems: Orthogonal Schmidt Decompositions

This repository provides code to generate examples corresponding to the propositions presented in our paper. It includes implementations of Schmidt decomposition formulas and methods for constructing mutually orthogonal two-qubit states.

## Overview
Schmidt decomposition is a fundamental tool in quantum information theory for analyzing entanglement in bipartite quantum systems. Our research presents explicit formulas for constructing mutually orthogonal quantum states in two-qubit systems. This repository provides implementations to verify and explore these results computationally.

## Paper
The full paper can be accessed on [arXiv:2503.06988](https://arxiv.org/abs/2503.06988).

## Repository Structure
```
📁 src/                # Source code for Schmidt decomposition
    📄 MyPrint.cpp
    📄 MyRandom.cpp
    📄 MyVec2.cpp
    📄 MyVec4.cpp
    📄 TwoQubitBasis.cpp
    📄 TwoQubitPureState.cpp
    📄 TwoQubitSchDecom.cpp
    📄 TestPaper.cpp
📁 include/            # Header files
    📄 MyPrint.h
    📄 MyRandom.h
    📄 MyVec2.h
    📄 MyVec4.h
    📄 TwoQubitBasis.h
    📄 TwoQubitPureState.h
    📄 TwoQubitSchDecom.h
    📄 TestPaper.h
📄 main.cpp            # Main script to execute decomposition
📄 README.md           # This file
```

## Language
This repository is implemented in **C++**.

## Usage
### Running the Code
1. Ensure that the `src/` and `include/` directories are correctly structured as shown above.
2. Open `main.cpp` and modify it to select the propositions or theorems you want to test.
3. Compile the code using:
```bash
g++ -I./include main.cpp src/*.cpp -o main && ./main
```
4. Run the compiled binary:
```bash
./main
```

### Selecting Specific Propositions or Theorems
To test specific propositions or theorems from the paper, uncomment only the desired functions in `main.cpp` and comment out the rest.

####  Proposition - Theorem Mapping
| Function | Description | Source File |
|----------|------------|-------------|
| `Proposition1()` | Diagonal two-qubit pure states | `TwoQubitPureState.cpp` |
| `Proposition2()` | Non-diagonal two-qubit pure states | `TwoQubitPureState.cpp` |
| `Proposition3()` - `Proposition8()` | Two-state orthogonal Schmidt decomposition | `TwoQubitBasis.cpp` |
| `Proposition9()` - `Proposition12()` | Three-state orthogonal Schmidt decomposition | `TwoQubitBasis.cpp` |
| `Theorem14()` - `Theorem21()` | Four-state orthogonal Schmidt decomposition | `TwoQubitBasis.cpp` |

Modify `main.cpp` and recompile to test only the desired cases.

## License
This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

## Citation
If you use this code, please cite our paper:
```bibtex
@article{Lee2025,
  author = {Yonghae Lee and Youngho Min and Sunghyun Bae and Youngrong Lim},
  title = {Formulas for Mutually Orthogonal Quantum States in Two-Qubit Systems: Orthogonal Schmidt Decompositions},
  journal = {arXiv preprint},
  year = {2025},
  archivePrefix = {arXiv},
  eprint = {2503.06988},
  primaryClass = {quant-ph}
}
```

## Contact
For any questions, feel free to reach out:
	Email: yonghaelee@kangwon.ac.kr
	[Website](https://sites.google.com/view/yonghaelee/home)