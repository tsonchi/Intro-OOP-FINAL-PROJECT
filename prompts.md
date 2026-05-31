
Fix creatine consumed status




why cant the user see that the dose is consumed rn in the dailytracker it wsays that creatine does hjasnt been consumed but it should be
8:58 PM


Worked for 4m 29s
The issue was copy behavior: juli.addSupplement(creatine) stored a copy of creatine while it was still “not consumed,” then creatine.consumeDose() changed only the local variable, not the copy inside juli.

I fixed it by adding User::consumeSupplement(...) in user.h (line 170), which updates the supplement stored inside the user’s inventory. Then main.cpp (line 73) now calls:

juli.consumeSupplement("Creatine");
I compiled and ran it. The daily report now shows:

Supplement: Creatine | Doses Available: 29 (Dose consumed)
Supplement: Protein Powder | Dose not consumed:

Edited 2 files
+23
-12
Undo
Review

main.cpp
+6
-6

user.h
+17
-6




9:03 PM
can you add whether a workout is complete throughout the day in the daily tracker and also in the week report add the records for this week
9:10 PM


Worked for 1m 11s
Done. I added workout completion into the daily tracker and weekly records into the week report.

Changes:

dailyTracker.h (line 12): added workoutComplete, markWorkoutComplete(), and getWorkoutComplete().
user.h (line 184): when addWorkoutRecord() is called, it marks the matching daily record as complete.
user.h (line 242): daily report now prints Workout: Complete or Workout: Not complete yet.
reportgenerator.h (line 24): weekly report now finds the best non-warmup set for each exercise this week.
main.cpp (line 129): moved the daily report print after workout loading, so the sample day shows the workout as complete.
Verified by compiling and running. Output now includes:

Workout:        Complete
and weekly records:

Weekly Records:
  Bench Press: 65 kg x 6 reps
  Overhead Press: 50 kg x 6 reps
  Squat: 100 kg x 6 reps

Edited 4 files
+125
-63
Undo
Review

dailyTracker.h
+24
-15

main.cpp
+13
-12

reportgenerator.h
+47
-19

Show 1 more file




9:11 PM
yo just add more things to the main file pls like more meals on different days and also if a workout is not in this week how will the weekly repoty know whether the workout is from this week
9:21 PM


Worked for 1m 42s
Done. I added more sample data in main.cpp:

More foods: oats, eggs, Greek yogurt, salmon.
More daily trackers/meals for 2026-18-05, 2026-19-05, 2026-20-05, and 2026-24-05.
A workout outside the week: Old Bench Day on 2026-10-05.
A workout inside the week: Pull Day on 2026-20-05.
Extra daily reports so you can see one day with workout complete and one without.
For your weekly report question: you were right, before it did not truly know. It only used the last 7 workout entries. I fixed that in reportgenerator.h so now you call:

ReportGenerator::generateWeeklyReport(
    juli,
    juli.getNutritionHistory(),
    juli.getWorkoutHistory(),
    "2026-17-05",
    "2026-23-05"
);
Now the report checks each workout date and only counts it if it falls between those two dates. I verified it works: the old 90 kg bench from 2026-10-05 is ignored, and the weekly report shows Bench Press: 65 kg x 6 reps from the actual week.


Edited 2 files
+170
-60
Undo
Review

main.cpp
+131
-46

reportgenerator.h
+39
-14




9:23 PM
ok now First record for Squat set to 100 kg.
========================================
DAILY NUTRITION REPORT FOR Yuliyan Tsonchev
Date: 2026-17-05
========================================
Calories:       843 / 2850 kcal
Protein:        78 / 126 g
Carbs:          110 / 444 g
Fats:           10 / 63 g
Workout:        Complete
----------------------------------------
Remaining: You need 2007 kcal MORE to hit your target.
Supplement: Creatine | Doses Available: 29 (Dose consumed)
Supplement: Protein Powder | Dose not consumed: 
========================================

========================================
DAILY NUTRITION REPORT FOR Yuliyan Tsonchev
Date: 2026-24-05
========================================
Calories:       835 / 2850 kcal
Protein:        77 / 126 g
Carbs:          60 / 444 g
Fats:           31 / 63 g
Workout:        Not complete yet
----------------------------------------
Remaining: You need 2015 kcal MORE to hit your target.
Supplement: Creatine | Doses Available: 29 (Dose consumed)
Supplement: Protein Powder | Dose not consumed: 
========================================
see that the dose is consumed again even tho it wasnt today can you fix that

Show less
9:46 PM



Worked for 44s
Fixed. The problem was that InventoryItem::isConsumedDose is global for the supplement, so once creatine was consumed once, every day showed it as consumed.

Now DailyTracker tracks supplement consumption per day:

dailyTracker.h: added markSupplementConsumed() and hasConsumedSupplement().
user.h: daily report now checks the selected day, not the global supplement flag.
main.cpp: marks creatine consumed only for 2026-17-05.
Verified output now shows:

Date: 2026-17-05
Supplement: Creatine | Doses Available: 29 (Dose consumed today)

Date: 2026-24-05
Supplement: Creatine | Doses Available: 29 (Dose not consumed today)

Edited 3 files
+52
-20
Undo
Review

dailyTracker.h
+27
-10

main.cpp
+1
-0

user.h
+24
-10










