# 💸 Cash Flow Minimizer

A full-featured **personal and group expense management app** with:
-  CLI-based settlement calculator (C)
-  AI-powered budget predictor (Python)
-  Graph-based transaction visualizer
-  Full web frontend using **React** + backend via **Flask**
-  Secure login system with token-based authentication
-  Email +  SMS/WhatsApp summary senders

---

##  Features Overview

###  User Authentication (JWT-based)
- Register and login securely
- Token-based route protection
- Local storage of JWT for session management

###  Group Expense Manager
- Add expenses for multiple people
- Calculate who owes whom
- Generate optimized settlement suggestions
- Visualize transactions as a graph (nodes + edges)
- Export PDF summary
- Send summary via Email or WhatsApp/SMS (Twilio)

###  Personal Expense Tracker
- Add daily expenses under categories
- View monthly/weekly/yearly breakdown
- AI prediction for future spending trends
- Set monthly budget and compare real spending
- Get feedback if under/over budget

###  Data Visualizations
- Bar charts for personal expenses
- Transaction flow graph for group settlement
- Integrated with Chart.js and NetworkX

### Full Web App Interface (React + Flask)
- Protected pages for Personal and Group views
- Clean navigation and responsive UI
- Toast notifications for all actions

---

##  Tech Stack

| Layer       | Technology                |
|-------------|---------------------------|
| Frontend    | React, React Router, Chart.js, Toastify |
| Backend     | Python (Flask), JWT, pandas, matplotlib |
| CLI Core    | C language (GCC-based)    |
| Auth        | JSON Web Tokens (JWT)     |
| Messaging   | Twilio API (SMS & WhatsApp) |
| Email       | Python SMTP/SSL           |
| Visuals     | Chart.js, Matplotlib, NetworkX |

---

##  Project Structure

```
CashFlow_050625/
├── src/                       # C CLI code
├── data/                      # Expense data (CSV files)
│   ├── personal_expenses.csv
│   ├── groups/
│   │   └── daman_trip.csv
├── python_utils/             # AI, graph, PDF, email, messaging
│   ├── ai_predictor.py
│   ├── group_graph.py
│   ├── message_sender.py
│   └── summary_generator.py
├── webapp/
│   ├── backend/              # Flask backend APIs
│   │   └── app.py
│   ├── frontend/             # React app
│   │   ├── src/
│   │   │   ├── pages/
│   │   │   │   ├── HomePage.jsx
│   │   │   │   ├── GroupSummary.jsx
│   │   │   │   ├── PersonalSummary.jsx
│   │   │   │   ├── Login.jsx
│   │   │   │   └── Register.jsx
│   │   │   ├── utils/auth.js
│   │   │   └── App.js
├── users.json                # Registered user data
├── README.md                 # Project documentation
```

---

###  Backend Setup (Flask)
```bash
cd webapp/backend
pip install -r requirements.txt  # or manually install flask, pandas, jwt, flask-cors
python app.py
```

### 💻 Frontend Setup (React)
```bash
cd webapp/frontend
npm install
npm start
```

### 🧮 CLI App (C)
```bash
cd src
gcc main.c -o cashflow
./cashflow
```

### 🤖 AI & Graph (Python)
```bash
cd python_utils
python ai_predictor.py
python group_graph.py
```

---

##  Sending Email or SMS

- Email: via `/api/send_email`
- SMS/WhatsApp: via `/api/send_message`
- Requires SMTP creds or Twilio setup

---

## To-Do / Possible Extensions
- Add income tracking & savings prediction
- Multi-language support
- CSV import/export from Excel
- Dark/light mode toggle
- Responsive mobile layout

---

## 🙌 Made with ❤️ by Shruti Verma (srTv)
Built for smart finance, college trips, roommates, or any group expenses!
