#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <sstream>
using namespace std;

// Function to compute the determinant
double compute_determinant(double A, double B, double C) {
    return pow(B, 2) - 4 * A * C;
}

// Function to classify the equation based on the determinant
void classify_equation(double determinant) {
    if (determinant > 0)
        cout << "Hyperbolic Equation" << endl;
    else if (determinant == 0)
        cout << "Parabolic Equation" << endl;
    else
        cout << "Elliptic Equation" << endl;
}

// Function to input coefficients
void input_coefficients(double& A, double& B, double& C, double& D, double& E, double& F) {
    cout << "Insert parameters for the PDE (A, B, C, D, E, F):\n";
    cout << "A: "; cin >> A;
    cout << "B: "; cin >> B;
    cout << "C: "; cin >> C;
    cout << "D: "; cin >> D;
    cout << "E: "; cin >> E;
    cout << "F: "; cin >> F;
}

// Function to evaluate expressions for coefficients
double evaluate_expression(const string& expr, double x) {
    if (expr == "x^2") {
        return x * x;
    } else if (expr == "exp(x)") {
        return exp(x);
    } else if (expr == "sin(x)") {
        return sin(x);
    } else if (expr == "cos(x)") {
        return cos(x);
    } else if (expr == "x") {
        return x;
    } else {
        cout << "Unsupported expression: \"" << expr << "\". Returning 0.\n";
        return 0;
    }
}

// Function to handle variable coefficients
void variable_classification(double A, double B, double C) {
    int num_vars;
    cout << "How many coefficients would you like to vary? (1, 2, or 3): ";
    cin >> num_vars;

    if (num_vars < 1 || num_vars > 3) {
        cout << "Invalid number of coefficients. Please select 1, 2, or 3.\n";
        return;
    }

    // Map to store coefficients and their functional forms
    map<string, string> variable_expressions;

    // Prompt the user to select and provide functional forms for the coefficients
    for (int i = 0; i < num_vars; i++) {
        string coeff, expression;
        cout << "Enter coefficient " << i + 1 << " to vary (A, B, or C): ";
        cin >> coeff;

        if (coeff != "A" && coeff != "B" && coeff != "C") {
            cout << "Invalid coefficient. Please select from A, B, or C.\n";
            return;
        }

        if (variable_expressions.find(coeff) != variable_expressions.end()) {
            cout << "Coefficient " << coeff << " has already been selected. Please choose a different one.\n";
            return;
        }

        cout << "Enter the functional form for " << coeff << " (e.g., x^2, exp(x)): ";
        cin >> expression;
        variable_expressions[coeff] = expression;
    }

    // Ask for the range of x
    double x_start, x_end, step_size;
    cout << "Enter the start value for x: ";
    cin >> x_start;
    cout << "Enter the end value for x: ";
    cin >> x_end;
    cout << "Enter the step size: ";
    cin >> step_size;

    if (step_size <= 0) {
        cout << "Step size must be greater than 0.\n";
        return;
    }

    // Evaluate for x values in the range
    for (double x = x_start; x <= x_end; x += step_size) {
        double temp_A = A, temp_B = B, temp_C = C;

        // Update coefficients based on variable expressions
        if (variable_expressions.find("A") != variable_expressions.end()) {
            temp_A = evaluate_expression(variable_expressions["A"], x);
        }
        if (variable_expressions.find("B") != variable_expressions.end()) {
            temp_B = evaluate_expression(variable_expressions["B"], x);
        }
        if (variable_expressions.find("C") != variable_expressions.end()) {
            temp_C = evaluate_expression(variable_expressions["C"], x);
        }

        double determinant = compute_determinant(temp_A, temp_B, temp_C);
        cout << "x = " << x << " -> A = " << temp_A << ", B = " << temp_B << ", C = " << temp_C
             << " -> Determinant = " << determinant << " -> ";
        classify_equation(determinant);
    }
}

int main() {
    double A, B, C, D, E, F;

    cout << "General Non-Homogeneous Second Order PDE:\n";
    cout << "A u_xx + B u_xy + C u_yy + D u_x + E u_y + F u = G(x, y)\n\n";

    // Input coefficients
    input_coefficients(A, B, C, D, E, F);

    // Compute and classify the equation
    double determinant = compute_determinant(A, B, C);
    cout << "\nFor the given coefficients:\n";
    cout << "Determinant = " << determinant << " -> ";
    classify_equation(determinant);

    // Ask user if they want to vary parameters
    char choice;
    cout << "\nWould you like to vary one or more coefficients (A, B, or C)? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        variable_classification(A, B, C);
    }
    char a; cin>>a;;
    return 0;
}
