using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace eVMS.Model
{
    public class Person
    {
        public string Username { get; set; }
        public string FullName { get; set; }

        public string Password { get; set; }
        public string Sex { get; set; }
        public string Email { get; set; }
        public string Address { get; set; }
        public DateTime Birthday { get; set; }
        public string Phone { get; set; }
        public int RoleId { get; set; }
        public string RoleName { get; set; }

        public List<Vms> Vms { get; set; }
    }
}
