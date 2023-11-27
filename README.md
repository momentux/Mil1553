# Mil

5.7 mcx_Create_BusList_Element

Specifying statuses on Status Word 1/2 it is injected and applies only to a situation when the Tester
is BC and the RT/s is set to be simulated by the Tester.
The use case for it is when testing a monitor unit (UUT) that is connected to the Tester and you want to verify
various statuses are received ok on the monitor’s side.

## Field Description
### Command MIL-STD-1553 command word #1.

Bits 11–15:
00000 – 11110:
Case – One command word: RT ID number of the transmitting RT (data source)
Case – Two command words: RT ID number of the receiving RT (data sink)
11111: Broadcast (BCST)

Bit 10:
1 – transmit command
0 – receive command

Bits 5 – 9:
00001 – 11110: Sub-address
00000, 11111: Mode command 

Bits 0 – 4:
For either the count of data words or the mode code, depending on the value in bits 5-9.

### wCommand2 MIL-STD-1553 command word #2
(for RT-to-RT type and RT-to-broadcast type only)

Bits 11–15:
RT ID number of the transmitting RT
(data source)

Bit 10 must be 1
See the table in the Message Formats section of the Sital Tester-1553 User
Manual, which lists the possible commands and shows where a second RT
participates.
StatusWord1 Transmission status, if any, with most recent transmission of this message.
This status word is filled only where relevant.
StatusWord2 Reception status, if any, with most recent transmission of this message.
This status word is filled only where relevant.