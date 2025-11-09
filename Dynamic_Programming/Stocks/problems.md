## **1️⃣ Best Time to Buy and Sell Stock I**

**Leetcode 121** – [Link](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)
**Problem:** You are given an array of stock prices. You may **buy and sell only once**. Maximize profit.

**Key Idea:**

* Track the **minimum price so far** and compute `profit = current_price - min_price`.
* No need for DP array here; greedy works.

**Learning Outcome:**

* Base case for stock DP: “profit = sell - buy”.

---

## **2️⃣ Best Time to Buy and Sell Stock II**

**Leetcode 122** – [Link](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/)
**Problem:** You can buy/sell **multiple times**. Maximize profit.

**Key Idea:**

* Either take every **upward slope**, i.e., `profit += max(0, prices[i] - prices[i-1])`.
* Or DP: `hold[i] = max(hold[i-1], cash[i-1]-price)`; `cash[i] = max(cash[i-1], hold[i-1]+price)`

**Learning Outcome:**

* Introduces **multiple transactions**, basic state: hold or cash.

---

## **3️⃣ Best Time to Buy and Sell Stock III**

**Leetcode 123** – [Link](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)
**Problem:** You may make **at most 2 transactions**.

**Key Idea:**

* DP states: `dp[k][i] = max profit up to day i with at most k transactions`.
* Transition: `dp[k][i] = max(dp[k][i-1], prices[i] + max_diff)`

  * `max_diff = max(max_diff, dp[k-1][j] - prices[j])`

**Learning Outcome:**

* Introduces **transaction count as a state**, key DP pattern.

---

## **4️⃣ Best Time to Buy and Sell Stock IV**

**Leetcode 188** – [Link](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/)
**Problem:** At most `k` transactions allowed.

**Key Idea:**

* Generalize previous problem: `dp[k][i]` as max profit with `k` transactions by day `i`.
* Same transition as Stock III, generalized to `k`.

**Learning Outcome:**

* Learn **how to extend DP for k transactions**.

---

## **5️⃣ Best Time to Buy and Sell Stock with Cooldown**

**Leetcode 309** – [Link](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)
**Problem:** After selling, you cannot buy the next day (1-day cooldown).

**Key Idea:**

* States:

  * `hold[i] = max(hold[i-1], rest[i-1] - price)`
  * `sold[i] = hold[i-1] + price`
  * `rest[i] = max(rest[i-1], sold[i-1])`

**Learning Outcome:**

* Introduces **extra states** due to cooldown.

---

## **6️⃣ Best Time to Buy and Sell Stock with Transaction Fee**

**Leetcode 714** – [Link](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)
**Problem:** Each transaction costs a fee.

**Key Idea:**

* Modify Stock II:

  * `hold[i] = max(hold[i-1], cash[i-1] - price)`
  * `cash[i] = max(cash[i-1], hold[i-1] + price - fee)`

**Learning Outcome:**

* Learn how **additional constraints** like fees modify DP transitions.

---

## **7️⃣ Best Time to Buy and Sell Stock with K Transactions and Cooldown/Fee (Hard Variants)**

* Combines **transaction limit**, **cooldown**, **fee** into one generalized DP.
* State: `dp[i][k][0/1]`

  * i = day, k = remaining transactions, 0/1 = holding/not holding.

**Learning Outcome:**

* Understand **multi-dimensional DP with constraints**.
* Pattern: `[day][transactions_left][holding_state]` → typical for most stock problems.

---

### **Key DP Patterns for Stocks**

1. **States:**

   * `hold` → currently holding a stock
   * `cash` → currently not holding
   * `transactions_left` → remaining transactions
   * `rest` → cooldown states

2. **Transitions:**

   * `hold[i] = max(hold[i-1], cash[i-1] - price)`
   * `cash[i] = max(cash[i-1], hold[i-1] + price)`
   * Add `-fee` or `cooldown` when needed

3. **Optimization:**

   * Space: store only `prev_day` states → O(1) space.
   * Time: usually O(n\*k) for k transactions.

---

### **Suggested Learning Path**

1. Stock I → greedy, single transaction.
2. Stock II → multiple transactions, simple DP.
3. Stock III → max 2 transactions, DP with transaction count.
4. Stock IV → generalize to k transactions.
5. Stock with Cooldown → add extra states.
6. Stock with Fee → modify transitions.
7. Combine constraints → generalized state-based DP.
