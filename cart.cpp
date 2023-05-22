#include <iostream>
#include <iomanip>//
#include <cmath>

using namespace std;

// Catalog information
string products[] = {"Product A", "Product B", "Product C"};
double prices[] = {20.0, 40.0, 50.0};

// Discount rules
const string flat10DiscountRule = "flat_10_discount";
const string bulk5DiscountRule = "bulk_5_discount";
const string bulk10DiscountRule = "bulk_10_discount";
const string tiered50DiscountRule = "tiered_50_discount";

// Fee constants
const double giftWrapFee = 1.0;
const int unitsPerPackage = 10;
const double shippingFeePerPackage = 5.0;

// Function to calculate the discount amount based on the given rule
double calculateDiscount(int quantity, double price, string rule) {
    if (rule == bulk5DiscountRule && quantity > 10) {
        return (price * quantity) * 0.05;
    } else if (rule == bulk10DiscountRule && quantity > 20) {
        return (price * quantity) * 0.10;
    } else if (rule == tiered50DiscountRule && quantity > 30 && quantity <= 50) {
        int discountedQuantity = max(quantity - 15, 0);
        return (price * discountedQuantity) * 0.50;
    } else if (rule == flat10DiscountRule && price * quantity > 200) {
        return 10.0;
    }

    return 0.0; // No discount applicable
}

// Function to find the best discount rule for a given product quantity and price
string findBestDiscount(int quantity, double price) {
    string bestDiscount = "";
    double maxDiscount = 0.0;

    double bulk5Discount = calculateDiscount(quantity, price, bulk5DiscountRule);
    double bulk10Discount = calculateDiscount(quantity, price, bulk10DiscountRule);
    double tiered50Discount = calculateDiscount(quantity, price, tiered50DiscountRule);
    double flat10Discount = calculateDiscount(quantity, price, flat10DiscountRule);

    if (bulk5Discount > maxDiscount) {
        maxDiscount = bulk5Discount;
        bestDiscount = bulk5DiscountRule;
    }
    if (bulk10Discount > maxDiscount) {
        maxDiscount = bulk10Discount;
        bestDiscount = bulk10DiscountRule;
    }
    if (tiered50Discount > maxDiscount) {
        maxDiscount = tiered50Discount;
        bestDiscount = tiered50DiscountRule;
    }
    if (flat10Discount > maxDiscount) {
        maxDiscount = flat10Discount;
        bestDiscount = flat10DiscountRule;
    }

    return bestDiscount;
}

int main() {
    // Input quantities and gift wrap choices
    int quantities[3];
    bool giftWrap[3];

    for (int i = 0; i < 3; i++) {
        cout << products[i] << ":" << endl;
        cout << "Quantity: ";
        cin >> quantities[i];
        cout << "Gift wrap? (1 for Yes, 0 for No): ";
        cin >> giftWrap[i];
    }

    // Calculate totals
    double subtotal = 0.0;
    double totalDiscount = 0.0;
    string bestDiscount = "";

    for (int i = 0; i < 3; i++) {
        double productTotal = prices[i] * quantities[i];
        string currentBestDiscount = findBestDiscount(quantities[i], prices[i]);
        double discountAmount = calculateDiscount(quantities[i], prices[i], currentBestDiscount);
        double discountedTotal = productTotal - discountAmount;

        if (discountAmount > 0 && discountAmount > totalDiscount) {
            totalDiscount = discountAmount;
            bestDiscount = currentBestDiscount;
        }

        cout << products[i] << " - Quantity: " << quantities[i] << " - Total: $" << fixed << setprecision(2) << productTotal << endl;
        subtotal += discountedTotal;
    }

    // Calculate shipping fee and gift wrap fee
    int totalQuantity = quantities[0] + quantities[1] + quantities[2];
    int totalPackages = ceil(static_cast<double>(totalQuantity) / unitsPerPackage);
    double shippingFee = totalPackages * shippingFeePerPackage;
    double giftWrapTotal = 0.0;

    for (int i = 0; i < 3; i++) {
        if (giftWrap[i]) {
            giftWrapTotal += quantities[i] * giftWrapFee;
        }
    }

    // Calculate grand total
    double grandTotal = subtotal + shippingFee + giftWrapTotal - totalDiscount;

    cout << "----------------------------------------" << endl;
    cout << "Subtotal: $" << fixed << setprecision(2) << subtotal << endl;
    
    if (!bestDiscount.empty()) {
        cout << "Discount Applied: " << bestDiscount << " - $" << totalDiscount << endl;
    }

    cout << "Shipping Fee: $" << fixed << setprecision(2) << shippingFee << " (" << totalPackages << " package(s))" << endl;
    cout << "Gift Wrap Fee: $" << fixed << setprecision(2) << giftWrapTotal << endl;
    cout << "Total: $" << fixed << setprecision(2) << grandTotal << endl;

    return 0;
}
