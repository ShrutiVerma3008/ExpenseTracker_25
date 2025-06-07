# budget_predictor.py
import pandas as pd
from sklearn.linear_model import LinearRegression
import matplotlib.pyplot as plt
import datetime
import os

DATA_PATH = "../data/personal_expenses.csv"

# Step 1: Load and preprocess data
def load_data():
    if not os.path.exists(DATA_PATH):
        print("Expense CSV not found.")
        return None
    df = pd.read_csv(DATA_PATH, names=["date", "category", "amount"])
    df["date"] = pd.to_datetime(df["date"], errors='coerce')
    df = df.dropna(subset=["date"])
    df["month"] = df["date"].dt.to_period("M")
    return df

# Step 2: Aggregate by month
def prepare_monthly_data(df):
    monthly = df.groupby("month")["amount"].sum().reset_index()
    monthly["month"] = monthly["month"].astype(str)
    monthly["month_num"] = range(1, len(monthly) + 1)
    return monthly

# Step 3: Train model and predict next month
def predict_next(monthly):
    X = monthly[["month_num"]]
    y = monthly["amount"]

    model = LinearRegression()
    model.fit(X, y)

    next_month = [[len(monthly) + 1]]
    prediction = model.predict(next_month)[0]

    print("\n🔮 Budget Prediction Result 🔮")
    print(f"Estimated Expense for Next Month: Rs {prediction:.2f}")

    return prediction

# Step 4: Optional - Show chart
def plot_chart(monthly, prediction):
    plt.plot(monthly["month"], monthly["amount"], marker='o', label="Actual")
    plt.axhline(prediction, color='r', linestyle='--', label=f"Predicted: {prediction:.2f}")
    plt.xticks(rotation=45)
    plt.xlabel("Month")
    plt.ylabel("Amount Spent (Rs)")
    plt.title("Monthly Expense Trend")
    plt.legend()
    plt.tight_layout()
    plt.show()

# Main Execution
if __name__ == "__main__":
    df = load_data()
    if df is not None and not df.empty:
        monthly = prepare_monthly_data(df)
        prediction = predict_next(monthly)
        plot_chart(monthly, prediction)
    else:
        print("No valid expense data to analyze.")
