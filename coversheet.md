Project #8 <Circuit Simulator>
CS 1220 – Spring 2026
<Mark St. Michell and Davis Brooks>

Note: You may not use generative AI to complete this coversheet.

# Requirements
Restate the problem specification, and any detailed requirements

This project required us to create a simulator which could take 2 input files and use the wire values specified to create a waveform accordingly. The project required us to create Wire, Gate, and Event classes. While the wire and gate clases are fairly self explanatory, the Event class was used as the primary way in which we simiulated the program. We created events which needed handled, and each event accounted for the value of a wire at a specific time. After all the events were handled, the program would finish. We were required to handle a few kinds of gates: NOT, AND, OR, NAND, NOR, XOR and XNOR gates. Each gate (except the NOT gate) were two input gates.
# Design
How did you attack the problem? What choices did you make in your design, and why? Show class diagrams for more complex designs.

We began attacking the problem by working on the Gate and Wire classes, which were needed for the interim assignment. After the interim, we sat down with a whiteboard and talked about all of the implementation we would need to do so that we would not be coding blindly. We decided that we would keep int main() {} as short as possible so that we could structure and debug our code in a way that was easy to read and change as necessary. In our main.cpp file, we used a few valuable functions to help keep int main() concise: initializeCircuitEvents, initalizeWiresAndGates, handleEvent, printCircuit, getWireByIndex, and a few more. These were extremely valuable because they allowed our classes to remain focused on their purposes and our main program to be readable. In our design, the handleEvents function was the most difficult to write because it relied on the most complex logic of the program. We initially tried solving the problem without consulting the Canvas resources, which forced us to waste a lot of time debugging faulty logic. Finally, we read the resources on Canvas which directed our logic and allowed us to complete the project. 
# Security Analysis
State the potential security vulnerabilities of your design. How could these vulnerabilities be exploited by an adversary? What would be the impact if the vulnerability is exploited?

I am unaware of any security vulnerabilities or ways our code could be exploited.
# Implementation
Outline any interesting implementation details.


# Testing
Explain how you tested your program, enumerating the tests if possible.
Explain why your test set was sufficient to believe that the software is working properly,
i.e., what were the range of possibilities of errors that you were testing for.


# AI Use
How did you use generative AI in this project?  Be specific!

The assignment description had a strict no AI policy, so we did not use AI.
# Summary/Conclusion
Present your results. Did it work properly? Are there any limitations? If it is an analysis-type project, this section may be significantly longer than for a simple implementation-type project.


# Lessons Learned
List any lessons learned, especially in regards to AI use.

One of the biggest lessons for this project was learning how to code in a group setting. We had not extensively used GitHub to collaborate before, so we had to practice creating and working in branches which we could then review and merge later. Additionaly, this was our first project where we had to integrate multiple classes at once, so it was very valuable to practice organizing and implementing a larger project. As a whole, this project taught us how to design classes and implement them to simplify implementation and therefore enhance our project.
# Time Spent
Approximately how much time did you spend on this project?

We have spent approximately 10 hours each on this project.