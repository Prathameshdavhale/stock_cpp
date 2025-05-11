#include <iostream>
#include <cmath>
using namespace std;

class StockPrice {
public:
    int timestamp;
    float price;
    StockPrice* next;

    StockPrice(int t, float p) : timestamp(t), price(p), next(nullptr) {}
};

class StockTracker {
private:
    StockPrice* head;

public:
    StockTracker() : head(nullptr) {}

    void insertPrice(int timestamp, float price) {
        StockPrice* newNode = new StockPrice(timestamp, price);
        if (!head) {
            head = newNode;
        } else {
            StockPrice* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        cout << "✅ New entry added: [Timestamp: " << timestamp << ", Price: ₹" << price << "]\n";
    }

    void updatePrice(int timestamp, float newPrice) {
        StockPrice* temp = head;
        while (temp) {
            if (temp->timestamp == timestamp) {
                temp->price = newPrice;
                cout << "📝 Price at timestamp " << timestamp << " has been updated to ₹" << newPrice << ".\n";
                return;
            }
            temp = temp->next;
        }
        cout << "⚠️ Sorry, no record found for timestamp " << timestamp << ".\n";
    }

    void deleteByTimestamp(int timestamp) {
        if (!head) {
            cout << "📭 There's no data to delete.\n";
            return;
        }

        if (head->timestamp == timestamp) {
            StockPrice* toDelete = head;
            head = head->next;
            delete toDelete;
            cout << "🗑️ Entry at timestamp " << timestamp << " has been removed.\n";
            return;
        }

        StockPrice* temp = head;
        while (temp->next && temp->next->timestamp != timestamp)
            temp = temp->next;

        if (!temp->next) {
            cout << "⚠️ No entry found for timestamp " << timestamp << ".\n";
            return;
        }

        StockPrice* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        cout << "🗑️ Entry at timestamp " << timestamp << " deleted successfully.\n";
    }

    void searchByTimestamp(int timestamp) {
        StockPrice* temp = head;
        while (temp) {
            if (temp->timestamp == timestamp) {
                cout << "🔍 Found: Price at timestamp " << timestamp << " is ₹" << temp->price << ".\n";
                return;
            }
            temp = temp->next;
        }
        cout << "❌ No data found for timestamp " << timestamp << ".\n";
    }

    void displayPrices() {
        if (!head) {
            cout << "📭 No stock entries available to show.\n";
            return;
        }

        cout << "\n📊 Current Stock Price Records:\n";
        cout << "--------------------------------\n";
        StockPrice* temp = head;
        while (temp) {
            cout << "⏱️ Timestamp: " << temp->timestamp << " | 💰 Price: ₹" << temp->price << "\n";
            temp = temp->next;
        }
    }

    void countEntries() {
        int count = 0;
        StockPrice* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        cout << "🔢 Total number of stock entries: " << count << "\n";
    }

    void sortBy(bool byPrice = false, bool ascending = true) {
        if (!head || !head->next) return;

        for (StockPrice* i = head; i && i->next; i = i->next) {
            for (StockPrice* j = i->next; j; j = j->next) {
                bool shouldSwap = byPrice ?
                    (ascending ? i->price > j->price : i->price < j->price) :
                    (ascending ? i->timestamp > j->timestamp : i->timestamp < j->timestamp);

                if (shouldSwap) {
                    swap(i->timestamp, j->timestamp);
                    swap(i->price, j->price);
                }
            }
        }
        cout << "✅ Data sorted by " << (byPrice ? "price" : "timestamp") << " in " 
             << (ascending ? "ascending" : "descending") << " order.\n";
    }

    void findStatistics() {
        if (!head) {
            cout << "📭 No data available for statistics.\n";
            return;
        }

        float maxP = head->price, minP = head->price, sum = 0;
        int count = 0;
        StockPrice* temp = head;

        while (temp) {
            maxP = max(maxP, temp->price);
            minP = min(minP, temp->price);
            sum += temp->price;
            count++;
            temp = temp->next;
        }

        float avg = sum / count;
        float variance = 0;
        temp = head;
        while (temp) {
            variance += pow(temp->price - avg, 2);
            temp = temp->next;
        }
        float stddev = sqrt(variance / count);

        cout << "\n📈 Stock Price Summary:\n";
        cout << "-------------------------\n";
        cout << "🔺 Highest Price: ₹" << maxP << "\n";
        cout << "🔻 Lowest Price : ₹" << minP << "\n";
        cout << "📊 Average Price: ₹" << avg << "\n";
        cout << "📏 Price Range  : ₹" << (maxP - minP) << "\n";
        cout << "📐 Std Deviation: " << stddev << "\n";
    }

    void clearAll() {
        while (head) {
            StockPrice* temp = head;
            head = head->next;
            delete temp;
        }
        cout << "🧹 All stock data has been cleared.\n";
    }
};

int main() {
    StockTracker tracker;
    int choice;

    do {
        cout << "\n================ 📈 Stock Market Price Tracker ================\n";
        cout << "1. ➕ Add New Stock Price\n";
        cout << "2. 📝 Update Price by Timestamp\n";
        cout << "3. ❌ Delete Price by Timestamp\n";
        cout << "4. 🔍 Search Price by Timestamp\n";
        cout << "5. 📃 View All Stock Prices\n";
        cout << "6. 🔢 Count All Entries\n";
        cout << "7. 🔽 Sort by Timestamp (Asc)\n";
        cout << "8. 🔽 Sort by Price (Asc)\n";
        cout << "9. 📈 Show Statistics\n";
        cout << "10. 🧹 Clear All Records\n";
        cout << "11. 🚪 Exit Program\n";
        cout << "===============================================================\n";
        cout << "👉 Your choice: ";
        cin >> choice;

        int timestamp;
        float price;

        switch (choice) {
            case 1:
                cout << "⏱️ Enter timestamp: ";
                cin >> timestamp;
                cout << "💰 Enter stock price (₹): ";
                cin >> price;
                tracker.insertPrice(timestamp, price);
                break;

            case 2:
                cout << "⏱️ Enter timestamp to update: ";
                cin >> timestamp;
                cout << "💸 Enter new price (₹): ";
                cin >> price;
                tracker.updatePrice(timestamp, price);
                break;

            case 3:
                cout << "⏱️ Enter timestamp to delete: ";
                cin >> timestamp;
                tracker.deleteByTimestamp(timestamp);
                break;

            case 4:
                cout << "⏱️ Enter timestamp to search: ";
                cin >> timestamp;
                tracker.searchByTimestamp(timestamp);
                break;

            case 5:
                tracker.displayPrices();
                break;

            case 6:
                tracker.countEntries();
                break;

            case 7:
                tracker.sortBy(false, true);
                break;

            case 8:
                tracker.sortBy(true, true);
                break;

            case 9:
                tracker.findStatistics();
                break;

            case 10:
                tracker.clearAll();
                break;

            case 11:
                cout << "👋 Thank you for using the Stock Tracker. Have a great day!\n";
                break;

            default:
                cout << "❗ Invalid option. Please try again.\n";
        }

    } while (choice != 11);

    return 0;
}
