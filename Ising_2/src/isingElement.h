#ifndef ISINGELEMENT_H_
#define ISINGELEMENT_H_

class element
{
private:
	int spin;

public:
	void setSpin(int sp);
	int getSpin();
};

void element::setSpin(int sp)
{
	spin = sp;
}

int element::getSpin()
{
	return spin;
}

#endif /* ISINGELEMENT_H_ */
