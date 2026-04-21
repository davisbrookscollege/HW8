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

One interesting implementation detail for this project is how we wrote the evaluate() function for the gate class. We ended up defaulting one of the two parameters to allow us to evaluate a gate with a potential input, without setting the input wire. This helped us fix a big error where our program would break when it experienced feedback in the circuit. To complete this implementation, we added a 4th wire state called DEFAULTED, which we used to determine if we were calling the function to evaluate the current wire's state, or a possible future state. Once we implemented this, we were able to fix the feedback error we had experienced. As mentioned above, one of the major implementation decisions was the choice to keep int main() short and readable using functions. One valuable function we wrote in this section was called getWireByIndex, which returned a pointer to a wire based on an inputed index. This was very valuable because it helped us organize our wires according to a set index for each wire. Keeping this consistent and organized helped us ensure we were using the right wire each time we evaluated an event.
# Testing
Explain how you tested your program, enumerating the tests if possible.
Explain why your test set was sufficient to believe that the software is working properly,
i.e., what were the range of possibilities of errors that you were testing for.

During initial development, there wasn't a lot of testing we could do without the basic logic of the program written. With this in mind, we ensured to add frequent comments so that we could review our code. We also ensured to keep the program free of compilation errors. When we had finished the program, we spent a lot of time testing the provided circuit files. We ran through these and found various errors. Primarily our errors were in the event handling stage of the program. After we fixed these, we ran through all of the provided files and compared our output to their known solutions. We believe this was sufficient testing because the provided files test each of the primary gates' functionality and our program's ability to handle feedback.
# AI Use
How did you use generative AI in this project?  Be specific!

The assignment description had a strict no AI policy, so we did not use AI.
# Summary/Conclusion
Present your results. Did it work properly? Are there any limitations? If it is an analysis-type project, this section may be significantly longer than for a simple implementation-type project.

The program works exactly as expected. The program is a simple version of a logic gate simulator, so there are many limitations, such as the fact that the simulation must be capped to a specific simulation length so that feedback loops don't evaluate indefinitely. The logic also requires a very specific format of the text files in order to parse the inputs correctly. Our program also doesn't take account if the user inputs a faulty file name. Since this is a terminal based program, this isn't an issue because the user can simply rerun the program and fix their input.
# Lessons Learned
List any lessons learned, especially in regards to AI use.

One of the biggest lessons for this project was learning how to code in a group setting. We had not extensively used GitHub to collaborate before, so we had to practice creating and working in branches which we could then review and merge later. Additionaly, this was our first project where we had to integrate multiple classes at once, so it was very valuable to practice organizing and implementing a larger project. As a whole, this project taught us how to design classes and implement them to simplify implementation and therefore enhance our project.
# Time Spent
Approximately how much time did you spend on this project?

We each have spent approximately 10 hours on this project.
