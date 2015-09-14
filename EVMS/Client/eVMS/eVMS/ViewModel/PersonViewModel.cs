using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using eVMS.Model;

namespace eVMS.ViewModel
{
    public class PersonViewModel:ViewModelBase
    {
        #region Mems
        Person _person;
        #endregion

        #region Construction
        /// Constructs the default instance of a SongViewModel
        public PersonViewModel()
        {
            Person = new Person();
            Vms = new List<Vms>();

        }
        #endregion

        #region Properties
        public Person Person
        {
            get
            {
                return _person;
            }
            set
            {
                _person = value;
            }
        }

        public string Username
        {
            get { return Person.Username; }
            set
            {
                Person.Username = value;
                if (Person.Username != value)
                {
                    Person.Username = value;
                    RaisePropertyChanged(() => Username);
                }
            }
        }

        public string FullName
        {
            get { return Person.FullName; }
            set
            {
                Person.FullName = value;
                if (Person.FullName != value)
                {
                    Person.FullName = value;
                    RaisePropertyChanged(() => FullName);
                }
            }
        }

        public string Password
        {
            get { return Person.Password; }
            set
            {
                Person.Password = value;
                if (Person.Password != value)
                {
                    Person.Password = value;
                    RaisePropertyChanged(() => Password);
                }
            }
        }

        public string Sex
        {
            get { return Person.Sex; }
            set
            {
                Person.Sex = value;
                if (Person.Sex != value)
                {
                    Person.Sex = value;
                    RaisePropertyChanged(() => Sex);
                }
            }
        }

        public DateTime Birthday
        {
            get { return Person.Birthday; }
            set
            {
                Person.Birthday = value;
                if (Person.Birthday != value)
                {
                    Person.Birthday = value;
                    RaisePropertyChanged(() => Birthday);
                }
            }
        }

        public string Phone
        {
            get { return Person.Phone; }
            set
            {
                Person.Phone = value;
                if (Person.Phone != value)
                {
                    Person.Phone = value;
                    RaisePropertyChanged(() => Phone);
                }
            }
        }

        public int RoleId
        {
            get { return Person.RoleId; }
            set
            {
                Person.RoleId = value;
                if (Person.RoleId != value)
                {
                    Person.RoleId = value;
                    RaisePropertyChanged(() => RoleId);
                }
            }
        }

        public string RoleName
        {
            get { return Person.RoleName; }
            set
            {
                Person.RoleName = value;
                if (Person.RoleName != value)
                {
                    Person.RoleName = value;
                    RaisePropertyChanged(() => RoleName);
                }
            }
        }
        public string Email
        {
            get { return Person.Email; }
            set
            {
                Person.Email = value;
                if (Person.Email != value)
                {
                    Person.Email = value;
                    RaisePropertyChanged(() => Email);
                }
            }
        }


        public string Address
        {
            get { return Person.Address; }
            set
            {
                Person.Address = value;
                if (Person.Address != value)
                {
                    Person.Address = value;
                    RaisePropertyChanged(() => Address);
                }
            }
        }

        public List<Vms> Vms
        {
            get { return Person.Vms; }
            set
            {
                Person.Vms = value;
                if (Person.Vms != value)
                {
                    Person.Vms = value;
                    RaisePropertyChanged(() => Vms);
                }
            }
        }

        #endregion
    }
}
