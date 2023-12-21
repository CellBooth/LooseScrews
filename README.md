# Team 5 - Loose Screws
EGR 3380 - Engineering Design I Transfer Subsystem. This repository documents the development process of our project in summary.

## Project Name: Interoperating Palletizing System
### Project Overview: 
Design, build, and test a system comprised of three interoperable subsystems for 
transporting cases of product into a work area, transporting pallets through the work area, and loading 
cases of product onto pallets for shipping.
See [video](https://photos.app.goo.gl/zRGr7y4jFxbNgpk97) and [compliance test](https://photos.app.goo.gl/28Aey4GzPfUhF6TU7).

### 5. Transfer Subsystem:
5.1. The Transfer Subsystem shall transfer Cases from the Case Export Positions to a Pallet 
positioned at the Pallet Loading Location as specified in the Operating Envelope of the Outbound
Subsystem

5.2. Cases shall be loaded onto Pallets in a 2 x 2 x 2 configuration as shown below:

5.2.1. The Transfer Subsystem shall sequentially move a Batch of four Cases from one of the 
Case Export Positions, followed by a Batch of four Cases from the other Case Export 
Position.

5.2.2. The Transfer Subsystem shall be capable of starting with either Batch.

5.2.3. An input interface shall be available to toggle which Batch is loaded first for each Pallet.

5.3. Within the Transfer Subsystem, the top surface of each Case shall at all times remain in a 
horizontal orientation. 

5.4. The top surface of the Pallet is marked to divide the surface evenly into four Quadrants. Each 
Case placed within a Quadrant must remain completely within the boundaries of a single 
Quadrant.

5.5. Each case must be placed on the Pallet with its top surface facing upwards and the product label 
facing outwards.

5.6. A Pallet Loading operation requires rework if any of the following occur:

5.6.1. At least one Case extends beyond the boundaries of a single Quadrant

5.6.2. There is at least one Case on the Pallet with its designated Top Surface not facing 
upwards

5.6.3. Errors in material handling including, but not limited to:

5.6.3.1. Cases shall not be knocked off the Pallet during operation of the Transfer
Subsystem 

5.6.3.2. Once engaged by the Transfer Subsystem at the Case Export Position, a Case 
shall remain continuously engaged by the Transfer Subsystem until the Case is 
loaded onto the Pallet

5.6.3.3. Cases shall only be placed within the Operating Envelope of the Outbound 
Subsystem when a Pallet is positioned at the Pallet Loading Location

5.7. Cases shall be loaded onto the Pallet in two Batches of four Cases each (e.g., four Green Cases 
followed by four Gold cases). Each case shall be transferred to a common X coordinate and Y 
coordinate with a tolerance of ± 0.15" as specified in the Operating Envelope; i.e. the Transfer 
Subsystem shall place a Case at the same position (X,Y,Z) each and every time. The Outbound 
Subsystem shall re-position the pallet after each Case is placed by the Transfer Subsystem such 
that an empty Quadrant is available for placement of the next Case.
