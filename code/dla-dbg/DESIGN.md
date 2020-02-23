# How to pass H/W Parameter?

H/W parameters (e.g. ``MAC_ARRAY_LENGTH``) are implicit, but necessary for behavior modeling.

Here are two deisngs under consideration
1. Extend BMContext
1. Extend TXNContext

The former one looks better.

# How to model bus congestion

Current timing model (TM), which returns static fetch/commit offsets from "instruction",
is inaccurate for DMA operations because it cannot model slowdown by bus congestion.

1. Introduce CInstr (Compute Instr) and MInstr (Memory-transfer Instr) classes which derives Instr class.
   - Restrict the current timing model only to CInstr.
1. Introduce CTranscation and MTransaction.
   - CInstr emits CTranscation, and MInstr emits MTranscation
   - MTransaction has additional attributes (managed by Session)
     - updated_at
     - bandwidth (bytes per tick)
     - transfered_bytes
     - total_bytes

1. Introduce CHECK event
   - For each CHECK event, Session inspects all the pending memory transcations, and update their state.
     - This update includes "bandwidth" readjust
   - When any MTranscation finishes, insert COMMIT event.

