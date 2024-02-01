-- It could be done step by step but for most queries i concatenate the previous queries.
-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Crime Scene Report
SELECT id,description FROM crime_scene_reports
WHERE year=2023 AND month=7 AND day=28 AND street="Humphrey Street";
/*
| 295 | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
| 297 | Littering took place at 16:36. No known witnesses.
*/
-- Bakery security logs.
SELECT activity,license_plate FROM bakery_security_logs
WHERE year=2023 AND month=7 AND day=28 AND hour=10 AND minute=15;
/* No Logs.*/

--Interviews.
SELECT id, name, transcript FROM interviews
WHERE year=2023 AND month=7 AND day=28;
/*
| id  |  name   |                                                                                                                                                     transcript                                                                                                                                                      |
+-----+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| 158 | Jose    | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”                                                                                                                               |
| 159 | Eugene  | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”                                                                                                                                                                                      |
| 160 | Barbara | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.                                                                                                                   |
| 161 | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| 162 | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| 163 | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
| 191 | Lily    | Our neighboring courthouse has a very annoying rooster that crows loudly at 6am every day. My sons Robert and Patrick took the rooster to a city far, far away, so it may never bother us again. My sons have successfully arrived in Paris.
*/
--Look security logs of bakery between 10.15 and 10.25. Cars which left the parking lot
SELECT id, activity, license_plate FROM bakery_security_logs
WHERE year=2023 AND month=7 AND day=28 AND hour=10 AND minute>=15 AND minute<=25;
/*
 id  | activity | license_plate |
+-----+----------+---------------+
| 260 | exit     | 5P2BI95       |
| 261 | exit     | 94KL13X       |
| 262 | exit     | 6P58WS2       |
| 263 | exit     | 4328GD8       |
| 264 | exit     | G412CB7       |
| 265 | exit     | L93JTIZ       |
| 266 | exit     | 322W7JE       |
| 267 | exit     | 0NTHK55       |
*/
-- ATM withdraws at Leggett Street
SELECT id, account_number, amount FROM atm_transactions
WHERE year=2023 AND month=7 AND day=28 AND atm_location="Leggett Street" AND transaction_type="withdraw";

/*
 id  | account_number | amount |
+-----+----------------+--------+
| 246 | 28500762       | 48     |
| 264 | 28296815       | 20     |
| 266 | 76054385       | 60     |
| 267 | 49610011       | 50     |
| 269 | 16153065       | 80     |
| 288 | 25506511       | 20     |
| 313 | 81061156       | 30     |
| 336 | 26013199       | 35     |
*/
-- Check bank accounts of withdrawers and learn their identity.
SELECT person_id, creation_year FROM bank_accounts
WHERE account_number IN
    (
        SELECT account_number FROM atm_transactions
        WHERE year=2023 AND month=7 AND day=28 AND atm_location="Leggett Street" AND transaction_type="withdraw"
    );
/*
| person_id | creation_year |
+-----------+---------------+
| 686048    | 2010          |
| 514354    | 2012          |
| 458378    | 2012          |
| 395717    | 2014          |
| 396669    | 2014          |
| 467400    | 2014          |
| 449774    | 2015          |
| 438727    | 2018          |
+-----------+---------------+
*/

--Find identity of people.
SELECT name, phone_number, passport_number, license_plate FROM people
WHERE id IN
    (
        SELECT person_id FROM bank_accounts
        WHERE account_number IN
        (
            SELECT account_number FROM atm_transactions
            WHERE year=2023 AND month=7 AND day=28 AND atm_location="Leggett Street" AND transaction_type="withdraw"
        )
    );
/*
|  name   |  phone_number  | passport_number | license_plate |
+---------+----------------+-----------------+---------------+
| Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
| Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
| Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
| Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
| Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
*/

--Match the license plate and person.
SELECT name, phone_number, passport_number, license_plate FROM people
WHERE license_plate IN
    (
        SELECT license_plate FROM people
        WHERE id IN
        (
            SELECT person_id FROM bank_accounts
            WHERE account_number IN
            (
                SELECT account_number FROM atm_transactions
                WHERE year=2023 AND month=7 AND day=28 AND atm_location="Leggett Street" AND transaction_type="withdraw"
            )
        )
    AND license_plate IN
        (
            SELECT license_plate FROM bakery_security_logs
            WHERE year=2023 AND month=7 AND day=28 AND hour=10 AND minute>=15 AND minute<=25
        )
    );
/*
| name  |  phone_number  | passport_number | license_plate |
+-------+----------------+-----------------+---------------+
| Iman  | (829) 555-5269 | 7049073643      | L93JTIZ       |
| Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
| Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
| Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
*/

--Check phone calls between 10.15 and 10.16.
SELECT id, caller, receiver FROM phone_calls
WHERE year=2023 AND month=7 AND day=28 AND duration<60; --duration in seconds
/*
| id  |     caller     |    receiver    |
+-----+----------------+----------------+
| 221 | (130) 555-0289 | (996) 555-8899 |
| 224 | (499) 555-9472 | (892) 555-8872 |
| 233 | (367) 555-5533 | (375) 555-8161 |
| 251 | (499) 555-9472 | (717) 555-1342 |
| 254 | (286) 555-6063 | (676) 555-6554 |
| 255 | (770) 555-1861 | (725) 555-3243 |
| 261 | (031) 555-6622 | (910) 555-3251 |
| 279 | (826) 555-1652 | (066) 555-9701 |
| 281 | (338) 555-6650 | (704) 555-2131 |
*/

-- Find the thieft.
SELECT name, passport_number
FROM people
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60
)
AND phone_number IN (
    SELECT phone_number
    FROM people
    WHERE license_plate IN (
        SELECT license_plate
        FROM people
        WHERE id IN (
            SELECT person_id
            FROM bank_accounts
            WHERE account_number IN (
                SELECT account_number
                FROM atm_transactions
                WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"
            )
        )
        AND license_plate IN (
            SELECT license_plate
            FROM bakery_security_logs
            WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
        )
    )
);

/*
| name  | passport_number |
+-------+-----------------+
| Diana | 3592750733      | Diana or Bruce is the thief.
| Bruce | 5773159633      |
+---------+-----------------+
*/

--Find flight id's using passport numbers.
SELECT flight_id, seat FROM passengers
WHERE passport_number IN
        (
        SELECT passport_number
        FROM people
        WHERE phone_number IN
        (
            SELECT caller
            FROM phone_calls
            WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60

        )
        AND phone_number IN
        (
            SELECT phone_number
            FROM people
            WHERE license_plate IN
            (
                SELECT license_plate
                FROM people
                WHERE id IN
                (
                    SELECT person_id
                    FROM bank_accounts
                    WHERE account_number IN
                    (
                        SELECT account_number
                        FROM atm_transactions
                        WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"
                    )
                )
            AND license_plate IN
            (
                SELECT license_plate
                FROM bakery_security_logs
                WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
            )
        )
    )

);
/*
| flight_id | seat |
+-----------+------+
| 18        | 4C   |
| 24        | 2C   |
| 36        | 4A   |
| 54        | 6C   |
*/
-- Find airport
SELECT id, abbreviation, full_name, city FROM airports
WHERE city="Fiftyville";

/*
| id | abbreviation |          full_name          |    city    |
+----+--------------+-----------------------------+------------+
| 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
*/

--Find destination airport id
SELECT id, origin_airport_id, destination_airport_id FROM flights
WHERE year=2023 AND month=7 AND day=29 AND origin_airport_id=
    (
        SELECT id FROM airports
        WHERE city="Fiftyville"
    )
    AND id IN
    (
        SELECT flight_id FROM passengers
        WHERE passport_number IN
        (
            SELECT passport_number
            FROM people
            WHERE phone_number IN
            (
                SELECT caller
                FROM phone_calls
                WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60

                UNION

                SELECT receiver
                FROM phone_calls
                WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60
            )
            AND phone_number IN (
                SELECT phone_number
                FROM people
                WHERE license_plate IN (
                    SELECT license_plate
                    FROM people
                    WHERE id IN (
                        SELECT person_id
                        FROM bank_accounts
                        WHERE account_number IN
                        (
                            SELECT account_number
                            FROM atm_transactions
                            WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"
                        )
                    )
                AND license_plate IN
                (
                    SELECT license_plate
                    FROM bakery_security_logs
                    WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
                )
            )
        )
    )
) ORDER BY hour;


-- Find airport (First flight)
SELECT id, abbreviation, full_name, city FROM airports
WHERE id=4;

/* NYC */

--Find 36th flight's passengers
SELECT passport_number FROM passengers WHERE flight_id=36 AND seat="4A";
-- Passport number 5773159633 matches with Bruce. Bruce is the thief.
--Find receiver of Bruce's call.
SELECT phone_number FROM people WHERE name="Bruce";
SELECT receiver FROM phone_calls WHERE caller="(367) 555-5533" AND year=2023 AND month=7 AND day=28 AND duration<60;
SELECT name FROM people WHERE phone_number="(375) 555-8161";
-- Robin is the ACCOMPLICE.
