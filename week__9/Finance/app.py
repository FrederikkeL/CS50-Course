import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash


from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    VALUE = {}
    total_stock_value = 0
    stock_value_usd = 0
    STOCKS = db.execute(
        "SELECT name, symbol, number FROM stocks WHERE userid = ?", session.get("user_id"))
    cash = db.execute("SELECT cash FROM users WHERE id = ?",
                      session.get("user_id"))[0]["cash"]
    for row in STOCKS:
        symbol = row['symbol']
        stock_price = lookup(symbol)['price']
        VALUE['symbol'] = usd(stock_price)
        stock_value = stock_price*row['number']
        total_stock_value = total_stock_value + stock_value
        stock_value_usd = usd(stock_value)
    total_assits = usd(total_stock_value+cash)
    cash_usd = usd(cash)
    return render_template("index.html", stocks=STOCKS, cash_usd=cash_usd, value=VALUE, stock_value_usd=stock_value_usd, total_assits=total_assits)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol to buy", 403)
        if not request.form.get("shares"):
            return apology("must provide number of shares to buy", 403)
        if request.form.get("shares").isdigit() == False:
            return apology("must provide number of shares to buy", 400)
        if int(request.form.get("shares")) < 1:
            return apology("must provide number of shares to buy", 400)
        buy = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        BUY = lookup(buy)
        if BUY == None:
            return apology("symbol not recognized", 400)
        price = int(BUY["price"])
        full_price = price*shares
        user_id = session.get("user_id")

        funds = db.execute("SELECT cash FROM users  WHERE id = ?", user_id)[
            0]["cash"]
        if full_price <= funds:
            number = db.execute(
                "SELECT number FROM stocks WHERE symbol = ? and userid=?", buy, user_id)
            if len(number) == 0:
                db.execute("INSERT INTO stocks(userid, name, symbol, number) VALUES (?,?,?,?)",
                           user_id, BUY["name"], buy, shares)

            else:
                new_shares = number[0]["number"] + shares
                db.execute(
                    "UPDATE stocks SET number = ? WHERE symbol = ? AND userid = ?", new_shares, buy, user_id)
            db.execute("INSERT INTO transactions(userid, type, name, symbol, stock, price, date) VALUES (?,?,?,?,?,?,?)",
                       user_id, "bought", BUY["name"], buy, shares, price, datetime.datetime.now())
            db.execute("UPDATE users SET cash = ? WHERE id = ?",
                       funds-full_price, user_id)
            return redirect("/")
        else:
            return apology("not enough funds", 403)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    user_id = session.get("user_id")
    TRANSACTIONS = db.execute(
        "SELECT * FROM transactions WHERE userid = ?", user_id)
    return render_template("history.html", transactions=TRANSACTIONS)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    QUOTE = []
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        symbol = request.form.get("symbol")
        QUOTE = lookup(symbol)
        # Ensure password was submitted
        if QUOTE == None:
            return apology("invalid symbol", 400)

        price = usd(QUOTE["price"])
        return render_template("quoted.html", quote=QUOTE, price=price)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password contains letters, numbers and symbol
        password = request.form.get("password")
        num_count = 0
        character_count = 0
        for character in password:
            character_count += 1
            if character.isdigit():
                num_count += 1

        if character_count < 8 or num_count < 1:
            return apology("password must be at least 8 characters long and contain letters and number", 400)

        # Ensure username exists and password is correct
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("passwords don't match", 400)
        result = db.execute(
            "SELECT id FROM users WHERE username = ?", request.form.get("username"))
        if len(result) > 0:
            return apology("username already used", 400)

        else:
            username = request.form.get("username")
            hash = generate_password_hash(request.form.get("password"))
            db.execute(
                "INSERT INTO users (username, hash, cash) VALUES(?, ?, ?)", username, hash, 10000)
            # Redirect user to login page
            return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol to sell", 400)
        if not request.form.get("shares"):
            return apology("must provide number of shares to sell", 400)
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        SELL = lookup(symbol)
        price = SELL["price"]
        full_price = price*shares
        user_id = session.get("user_id")
        funds = db.execute("SELECT cash FROM users  WHERE id = ?",
                           session.get("user_id"))[0]['cash']
        STOCKS = db.execute(
            "SELECT number FROM stocks WHERE userid = ? AND symbol = ?", user_id, symbol)[0]["number"]
        if STOCKS >= shares:
            db.execute("UPDATE stocks SET number = ? WHERE symbol = ? AND userid = ?",
                       STOCKS-shares, symbol, user_id)
            db.execute("UPDATE users SET cash = ? WHERE id = ?",
                       funds+full_price, user_id)
            db.execute("INSERT INTO transactions(userid, type, name, symbol, stock, price, date) VALUES (?,?,?,?,?,?,?)",
                       user_id, "sold", SELL["name"], symbol, shares, price, datetime.datetime.now())
            return redirect("/")
        else:
            return apology("stocks not found", 400)
    else:
        SYMBOLS = db.execute(
            "SELECT DISTINCT symbol, name FROM stocks WHERE userid = ?", session.get("user_id"))
        return render_template("sell.html", symbols=SYMBOLS)
