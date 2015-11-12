#ifndef SYMOPREPRESENTATION_HH
#define SYMOPREPRESENTATION_HH

#include <iostream>
#include <cmath>

#include "casm/CASM_global_definitions.hh"
#include "casm/container/Array.hh"


namespace CASM {
  class MasterSymGroup;
  class Permutation;
  class UnitCellCoord;


  ///\brief SymOpRepresentation is the base class for anything describes a symmetry operation
  class SymOpRepresentation {
  public:
    enum symmetry_type {identity_op, mirror_op, glide_op, rotation_op, screw_op, inversion_op, rotoinversion_op, invalid_op};

  protected:
    ///type of symmetry, given by one of the allowed values of symmetry_type
    mutable symmetry_type symmetry;

    /// Pointer to the MasterSymGroup where prototype of this SymOp lives
    MasterSymGroup const *m_master_group;

    ///Index into MasterSymGroup that specifies the operation
    Index op_index, rep_ID;


  public:
    SymOpRepresentation() : symmetry(invalid_op), m_master_group(NULL), op_index(-1), rep_ID(-1) {};
    SymOpRepresentation(const MasterSymGroup &_master_group, Index _rep_ID, Index _op_index) :
      symmetry(invalid_op), m_master_group(&_master_group), op_index(_op_index), rep_ID(_rep_ID) {};

    //SymOpRepresentation specifies how a symmetry operation acts on a certain type of object.
    //It is a virtual class, since we don't need to know the specifics of its behavior at higher levels of abstraction
    virtual ~SymOpRepresentation() {}; // = 0;

    virtual SymOpRepresentation *copy() const = 0;
    virtual double get_character() const {
      return NAN;
    };
    virtual Permutation  const *get_permutation() const {
      return NULL;
    };
    virtual Eigen::MatrixXd const *get_MatrixXd() const {
      return NULL;
    };

    virtual Array<UnitCellCoord> const *get_ucc_permutation() const {
      return NULL;
    };

    /// get pointer to matrix representation corresponding to rep_ID
    Eigen::MatrixXd const *get_matrix_rep(Index rep_ID) const;

    /// get pointer to permutation representation corresponding to rep_ID
    Permutation const *get_permutation_rep(Index rep_ID) const;

    /// get pointer to BasisPermute representation corresponding to rep_ID
    Array<UnitCellCoord> const *get_basis_permute_rep(Index rep_ID) const;

    /// get array of pointers to matrix representations for representations corresponding to rep_IDs
    Array<Eigen::MatrixXd const * > get_matrix_reps(Array<Index> rep_IDs) const;

    /// register a new representation for (*this) within m_master_group->representation(rep_ID)
    void register_rep(Index rep_ID, const SymOpRepresentation &op_rep) const;

    /// Set m_master_group, rep_ID, and op_index
    void set_identifiers(const MasterSymGroup &new_group, Index new_rep_ID, Index new_op_index);

    /// Change m_master_group and try to determine op_index by looking at new m_master_group
    void set_identifiers(const MasterSymGroup &new_group, Index new_rep_ID);

    /// const access of head group
    const MasterSymGroup &master_group() const {
      assert(m_master_group);
      return *m_master_group;
    }

    bool has_valid_master() const {
      return m_master_group != NULL;
    }

    void invalidate_index() {
      op_index = -1;
    }

    Index index()const {
      return op_index;
    };

    Index ind_inverse()const;

    Index ind_prod(const SymOpRepresentation &RHS)const;

    virtual jsonParser &to_json(jsonParser &json) const = 0;
    virtual void from_json(const jsonParser &json) = 0;
  };

  jsonParser &to_json(const SymOpRepresentation *rep, jsonParser &json);
  /// This allocates a new object to 'rep'.
  void from_json(SymOpRepresentation *rep, const jsonParser &json);

  jsonParser &to_json(const SymOpRepresentation::symmetry_type &stype, jsonParser &json);
  void from_json(SymOpRepresentation::symmetry_type &stype, const jsonParser &json);

}
#endif
