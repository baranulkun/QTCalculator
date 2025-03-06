# Qt Calculator

A simple calculator built with **Qt** that supports basic arithmetic operations.

## Features
- Responsive **QLineEdit** display for input and results
- **QPushButton**-based UI with stylish gradient design
- Supports **addition (+), subtraction (-), multiplication (*), and division (/)**
- Handles multiple operator inputs with priority-based evaluation
- Clear button (C) to reset the display
- Debugging output using **qDebug()** for calculations

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/baranulkun/QTCalculator.git
   cd QTCalculator
   ```
2. Open the project in Qt Creator or compile manually using **qmake** and **make**:
   ```bash
   qmake
   make
   ```
3. Run the executable:
   ```bash
   ./QTCalculator
   ```

## Usage
- Enter numbers using the UI buttons.
- Click on an operator (`+`, `-`, `*`, `/`) to perform operations.
- Press `=` to evaluate the expression.
- Press `C` to clear the display.

## Code Overview
- `MainWindow::setupUI()` → Initializes the calculator's UI.
- `MainWindow::onButtonClicked()` → Handles button clicks and updates the display.
- `MainWindow::hesapla()` → Evaluates the arithmetic expression, respecting operator precedence.


