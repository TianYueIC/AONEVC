//SCBButton.h

#ifndef CSCBButton_h
#define CSCBButton_h

class CSCBButton
{
public:
    CSCBButton();

    void Move(CPoint ptTo) {ptOrg = ptTo; };
    CRect GetRect() { return CRect(ptOrg, CSize(13, 13)); };
    void Paint(CDC* pDC);

    BOOL    bPushed;
    BOOL    bRaised;

protected:
    CPoint  ptOrg;
};
#endif //CSCBButton_h