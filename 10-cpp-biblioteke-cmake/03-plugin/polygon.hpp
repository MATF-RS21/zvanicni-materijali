
#ifndef POLYGON_HPP
#define POLYGON_HPP

// Apstraktni interfejs koji oslikava klasu.
// Konrektna implementacija mora da ga nasledi i da implementira odgovarajuce metode.
class polygon
{
protected:
    double side_length_;

public:
    polygon()
        : side_length_(0) {}

    virtual ~polygon() {}

    void set_side_length(double side_length)
    {
        side_length_ = side_length;
    }

    virtual double area() const = 0;
};

// Moramo sami da napisemo funkcije za instanciranje i brisanje.
typedef polygon *create_t();
typedef void destroy_t(polygon *);

#endif